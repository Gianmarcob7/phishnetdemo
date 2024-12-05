#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QUuid>
#include <QDir>
#include <stdexcept>

Database::Database() : connected(false) {
    try {
        connected = initializeDatabase();
        if (!connected) {
            qDebug() << "Failed to initialize database";
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception during database initialization:" << e.what();
        connected = false;
    }
}

Database::~Database() {
    try {
        if (db.isOpen()) {
            db.close();
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception during database cleanup:" << e.what();
    }
}

bool Database::initializeDatabase() {
    try {
        db = QSqlDatabase::addDatabase("QSQLITE");
        QString dbPath = QDir::currentPath() + "/scan_results.db";
        db.setDatabaseName(dbPath);
        
        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError().text();
            return false;
        }

        // Create tables if they don't exist
        QSqlQuery query(db);
        
        // Sessions table
        if (!query.exec("CREATE TABLE IF NOT EXISTS sessions "
                       "(session_id TEXT PRIMARY KEY, "
                       "scan_type TEXT, "
                       "start_time TEXT, "
                       "end_time TEXT, "
                       "files_scanned INTEGER, "
                       "threats_found INTEGER)")) {
            qDebug() << "Failed to create sessions table:" << query.lastError().text();
            return false;
        }

        // Scan results table
        if (!query.exec("CREATE TABLE IF NOT EXISTS scan_results "
                       "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "session_id TEXT, "
                       "file_path TEXT, "
                       "threat_name TEXT, "
                       "scan_date TEXT, "
                       "detected BOOLEAN, "
                       "FOREIGN KEY(session_id) REFERENCES sessions(session_id))")) {
            qDebug() << "Failed to create scan_results table:" << query.lastError().text();
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        qDebug() << "Exception in initializeDatabase:" << e.what();
        return false;
    }
}

std::string Database::generateSessionId() {
    return QUuid::createUuid().toString(QUuid::WithoutBraces).toStdString();
}

std::vector<ScanSession> Database::getRecentSessions(int limit) {
    std::vector<ScanSession> sessions;
    
    try {
        if (!connected) {
            qDebug() << "Database not connected";
            return sessions;
        }

        QSqlQuery query(db);
        query.prepare("SELECT * FROM sessions ORDER BY start_time DESC LIMIT ?");
        query.addBindValue(limit);

        if (!query.exec()) {
            qDebug() << "Failed to query sessions:" << query.lastError().text();
            return sessions;
        }

        while (query.next()) {
            ScanSession session;
            session.session_id = query.value("session_id").toString().toStdString();
            session.scan_type = query.value("scan_type").toString().toStdString();
            session.start_time = query.value("start_time").toString().toStdString();
            session.end_time = query.value("end_time").toString().toStdString();
            session.files_scanned = query.value("files_scanned").toInt();
            session.threats_found = query.value("threats_found").toInt();
            sessions.push_back(session);
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception in getRecentSessions:" << e.what();
    }

    return sessions;
}

std::vector<ScanRecord> Database::getSessionResults(const std::string& session_id) {
    std::vector<ScanRecord> records;
    
    try {
        if (!connected) {
            qDebug() << "Database not connected";
            return records;
        }

        QSqlQuery query(db);
        query.prepare("SELECT * FROM scan_results WHERE session_id = ? ORDER BY scan_date DESC");
        query.addBindValue(QString::fromStdString(session_id));

        if (!query.exec()) {
            qDebug() << "Failed to query scan results:" << query.lastError().text();
            return records;
        }

        while (query.next()) {
            ScanRecord record;
            record.file_path = query.value("file_path").toString().toStdString();
            record.threat_name = query.value("threat_name").toString().toStdString();
            record.scan_date = query.value("scan_date").toString().toStdString();
            record.detected = query.value("detected").toBool();
            records.push_back(record);
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception in getSessionResults:" << e.what();
    }

    return records;
}

std::string Database::startSession(const std::string& scan_type) {
    try {
        if (!connected) {
            qDebug() << "Database not connected";
            return "";
        }

        current_session_id = generateSessionId();
        QSqlQuery query(db);
        query.prepare("INSERT INTO sessions (session_id, scan_type, start_time) "
                     "VALUES (?, ?, datetime('now', 'localtime'))");
        query.addBindValue(QString::fromStdString(current_session_id));
        query.addBindValue(QString::fromStdString(scan_type));

        if (!query.exec()) {
            qDebug() << "Failed to start session:" << query.lastError().text();
            return "";
        }

        return current_session_id;
    } catch (const std::exception& e) {
        qDebug() << "Exception in startSession:" << e.what();
        return "";
    }
}

void Database::endSession(int files_scanned, int threats_found) {
    try {
        if (!connected || current_session_id.empty()) {
            qDebug() << "Database not connected or no active session";
            return;
        }

        QSqlQuery query(db);
        query.prepare("UPDATE sessions SET "
                     "end_time = datetime('now', 'localtime'), "
                     "files_scanned = ?, "
                     "threats_found = ? "
                     "WHERE session_id = ?");
        query.addBindValue(files_scanned);
        query.addBindValue(threats_found);
        query.addBindValue(QString::fromStdString(current_session_id));

        if (!query.exec()) {
            qDebug() << "Failed to end session:" << query.lastError().text();
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception in endSession:" << e.what();
    }
}

void Database::logScanResult(const std::string& filepath, bool threat_detected, const std::string& threat_name) {
    try {
        if (!connected || current_session_id.empty()) {
            qDebug() << "Database not connected or no active session";
            return;
        }

        QSqlQuery query(db);
        query.prepare("INSERT INTO scan_results "
                     "(session_id, file_path, threat_name, scan_date, detected) "
                     "VALUES (?, ?, ?, datetime('now', 'localtime'), ?)");
        query.addBindValue(QString::fromStdString(current_session_id));
        query.addBindValue(QString::fromStdString(filepath));
        query.addBindValue(QString::fromStdString(threat_name));
        query.addBindValue(threat_detected);

        if (!query.exec()) {
            qDebug() << "Failed to log scan result:" << query.lastError().text();
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception in logScanResult:" << e.what();
    }
}

int Database::getDurationInMinutes(const ScanSession& session) {
    try {
        QDateTime startTime = QDateTime::fromString(QString::fromStdString(session.start_time), Qt::ISODate);
        QDateTime endTime = QDateTime::fromString(QString::fromStdString(session.end_time), Qt::ISODate);
        
        if (!startTime.isValid() || !endTime.isValid()) {
            qDebug() << "Invalid datetime format in session";
            return 0;
        }

        return static_cast<int>(startTime.secsTo(endTime) / 60);
    } catch (const std::exception& e) {
        qDebug() << "Exception in getDurationInMinutes:" << e.what();
        return 0;
    }
}

std::string Database::getScanSummary(const std::string& session_id) {
    try {
        if (!connected) {
            return "Database not connected";
        }

        QSqlQuery query(db);
        query.prepare("SELECT s.*, "
                     "(SELECT COUNT(*) FROM scan_results WHERE session_id = s.session_id AND detected = 1) as threats "
                     "FROM sessions s "
                     "WHERE s.session_id = ?");
        query.addBindValue(QString::fromStdString(session_id));

        if (!query.exec() || !query.first()) {
            qDebug() << "Failed to get scan summary:" << query.lastError().text();
            return "Failed to retrieve scan information";
        }

        QString summary = QString("Scan Summary\n\n"
                                "Scan Type: %1\n"
                                "Start Time: %2\n"
                                "End Time: %3\n"
                                "Files Scanned: %4\n"
                                "Threats Found: %5\n")
                             .arg(query.value("scan_type").toString())
                             .arg(query.value("start_time").toString())
                             .arg(query.value("end_time").toString())
                             .arg(query.value("files_scanned").toString())
                             .arg(query.value("threats").toString());

        // Add threat details if any were found
        if (query.value("threats").toInt() > 0) {
            QSqlQuery threatQuery(db);
            threatQuery.prepare("SELECT file_path, threat_name, scan_date "
                              "FROM scan_results "
                              "WHERE session_id = ? AND detected = 1");
            threatQuery.addBindValue(QString::fromStdString(session_id));

            if (threatQuery.exec()) {
                summary += "\nDetected Threats:\n";
                summary += "----------------\n";
                while (threatQuery.next()) {
                    summary += QString("\nFile: %1\n"
                                     "Threat: %2\n"
                                     "Detected: %3\n")
                                 .arg(threatQuery.value("file_path").toString())
                                 .arg(threatQuery.value("threat_name").toString())
                                 .arg(threatQuery.value("scan_date").toString());
                }
            }
        }

        return summary.toStdString();
    } catch (const std::exception& e) {
        qDebug() << "Exception in getScanSummary:" << e.what();
        return std::string("Error generating scan summary: ") + e.what();
    }
}