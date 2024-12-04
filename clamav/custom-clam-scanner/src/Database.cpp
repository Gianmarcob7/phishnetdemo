#include "Database.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

// Initialize database and create tables if they don't exist
Database::Database() {
    int rc = sqlite3_open("scan_results.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        createTables();
    }
}

// Create required database schema 
void Database::createTables() {
    const char* sql[] = {
        // Main table for scanning sessions
        R"(
        CREATE TABLE IF NOT EXISTS ScanSessions (
            session_id TEXT PRIMARY KEY,
            scan_type TEXT NOT NULL,
            start_time TIMESTAMP,
            end_time TIMESTAMP,
            files_scanned INTEGER,
            threats_found INTEGER
        );
        )",
        // Detailed scan results for each file
        R"(
        CREATE TABLE IF NOT EXISTS ScanResults (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            session_id TEXT,
            file_path TEXT NOT NULL,
            detected INTEGER NOT NULL,
            threat_name TEXT,
            scan_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(session_id) REFERENCES ScanSessions(session_id)
        );
        )"
    };

    for (const auto& query : sql) {
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, query, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
}

// Generate unique session ID from timestamp and hash
std::string Database::generateSessionId() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S_")
       << std::hex << std::hash<std::string>{}(std::to_string(time));
    return ss.str();
}

// Get formatted current timestamp 
std::string Database::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Create new scan session and store initial info
void Database::startSession(const std::string& scan_type) {
    current_session_id = generateSessionId();
    const char* sql = "INSERT INTO ScanSessions (session_id, scan_type, start_time) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, current_session_id.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, scan_type.c_str(), -1, SQLITE_STATIC);
        std::string timestamp = getCurrentTimestamp();
        sqlite3_bind_text(stmt, 3, timestamp.c_str(), -1, SQLITE_STATIC);
        
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

// Update session with final stats and generate report
void Database::endSession(int files_scanned, int threats_found) {
    const char* sql = "UPDATE ScanSessions SET end_time = ?, files_scanned = ?, threats_found = ? WHERE session_id = ?;";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::string timestamp = getCurrentTimestamp();
        sqlite3_bind_text(stmt, 1, timestamp.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, files_scanned);
        sqlite3_bind_int(stmt, 3, threats_found);
        sqlite3_bind_text(stmt, 4, current_session_id.c_str(), -1, SQLITE_STATIC);
        
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    generateReport(current_session_id);
}

// Store scan result for individual file
void Database::logScanResult(const std::string& filePath, bool detected, const std::string& threatName) {
    const char* sql = "INSERT INTO ScanResults (session_id, file_path, detected, threat_name) VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, current_session_id.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, filePath.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, detected ? 1 : 0);
        sqlite3_bind_text(stmt, 4, threatName.c_str(), -1, SQLITE_STATIC);
        
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

// Get most recent scan sessions, limited to specified count
std::vector<ScanSession> Database::getRecentSessions(int limit) {
    std::vector<ScanSession> sessions;
    const char* sql = R"(
        SELECT session_id, scan_type, start_time, end_time, files_scanned, threats_found 
        FROM ScanSessions 
        ORDER BY start_time DESC 
        LIMIT ?;
    )";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, limit);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            ScanSession session;
            session.session_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            session.scan_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            session.start_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            session.end_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            session.files_scanned = sqlite3_column_int(stmt, 4);
            session.threats_found = sqlite3_column_int(stmt, 5);
            sessions.push_back(session);
        }
        
        sqlite3_finalize(stmt);
    }
    
    return sessions;
}

// Get all scan results for a specific session
std::vector<ScanRecord> Database::getSessionResults(const std::string& session_id) {
    std::vector<ScanRecord> records;
    const char* sql = R"(
        SELECT file_path, detected, scan_date, threat_name 
        FROM ScanResults 
        WHERE session_id = ? 
        ORDER BY scan_date;
    )";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, session_id.c_str(), -1, SQLITE_STATIC);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            ScanRecord record;
            record.file_path = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            record.detected = sqlite3_column_int(stmt, 1) != 0;
            record.scan_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            record.threat_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            records.push_back(record);
        }
        
        sqlite3_finalize(stmt);
    }
    
    return records;
}

// Get summary of scan session stats
std::string Database::getScanSummary(const std::string& session_id) {
    std::stringstream summary;
    const char* sql = R"(
        SELECT scan_type, start_time, end_time, files_scanned, threats_found 
        FROM ScanSessions 
        WHERE session_id = ?;
    )";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, session_id.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            summary << "Scan Type: " << sqlite3_column_text(stmt, 0) << "\n"
                   << "Start Time: " << sqlite3_column_text(stmt, 1) << "\n"
                   << "End Time: " << sqlite3_column_text(stmt, 2) << "\n"
                   << "Files Scanned: " << sqlite3_column_int(stmt, 3) << "\n"
                   << "Threats Found: " << sqlite3_column_int(stmt, 4);
        }
        
        sqlite3_finalize(stmt);
    }
    
    return summary.str();
}

// Display formatted scan history with threat details
void Database::viewScanHistory() {
    auto sessions = getRecentSessions(10);  // Show last 10 scans
    
    if (sessions.empty()) {
        std::cout << "\nNo scan history found.\n";
        return;
    }

    std::cout << "\n=== Scan History ===\n";
    std::cout << std::string(100, '-') << "\n";
    std::cout << std::left
              << std::setw(25) << "Session ID"
              << std::setw(15) << "Type"
              << std::setw(20) << "Start Time"
              << std::setw(20) << "End Time"
              << std::setw(10) << "Files"
              << "Threats\n";
    std::cout << std::string(100, '-') << "\n";

    for (const auto& session : sessions) {
        std::cout << std::left
                  << std::setw(25) << session.session_id
                  << std::setw(15) << session.scan_type
                  << std::setw(20) << session.start_time
                  << std::setw(20) << (session.end_time.empty() ? "In Progress" : session.end_time)
                  << std::setw(10) << session.files_scanned
                  << session.threats_found << "\n";

        // Show details for any threats found
        if (session.threats_found > 0) {
            auto results = getSessionResults(session.session_id);
            for (const auto& result : results) {
                if (result.detected) {
                    std::cout << "  → Threat: " << result.threat_name 
                             << " in file: " << result.file_path << "\n";
                }
            }
            std::cout << "\n";
        }
    }
    std::cout << std::string(100, '-') << "\n";
}

// Generate detailed report file for scan session
void Database::generateReport(const std::string& session_id) {
    fs::create_directories("scan_reports");
    std::string filename = "scan_reports/scan_" + session_id + ".txt";
    std::ofstream report(filename);
    
    if (!report.is_open()) {
        std::cerr << "Failed to create report file" << std::endl;
        return;
    }

    report << getScanSummary(session_id) << "\n\n";

    // Add details of any threats found
    const char* threats_sql = "SELECT file_path, threat_name, scan_date FROM ScanResults "
                             "WHERE session_id = ? AND detected = 1;";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, threats_sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, session_id.c_str(), -1, SQLITE_STATIC);
        
        bool found_threats = false;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            if (!found_threats) {
                report << "Detected Threats:\n";
                report << "================\n\n";
                found_threats = true;
            }
            
            report << "File: " << sqlite3_column_text(stmt, 0) << "\n";
            report << "Threat: " << sqlite3_column_text(stmt, 1) << "\n";
            report << "Detection Time: " << sqlite3_column_text(stmt, 2) << "\n\n";
        }
        
        if (!found_threats) {
            report << "No threats were detected during this scan.\n";
        }
        
        sqlite3_finalize(stmt);
    }

    report.close();
    std::cout << "\nScan report generated: " << filename << std::endl;
}

// Clean up database connection
Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}