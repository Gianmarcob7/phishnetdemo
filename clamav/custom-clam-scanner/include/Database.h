// include/Database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <QSqlDatabase>
#include <QString>

struct ScanRecord {
    std::string file_path;
    std::string threat_name;
    std::string scan_date;
    bool detected;
};

struct ScanSession {
    std::string session_id;
    std::string scan_type;
    std::string start_time;
    std::string end_time;
    int files_scanned;
    int threats_found;
};

class Database {
public:
    Database();
    ~Database();
    
    bool isConnected() const { return connected; }
    std::vector<ScanSession> getRecentSessions(int limit = 100);  // Changed to accept limit parameter
    std::vector<ScanRecord> getSessionResults(const std::string& session_id);
    void logScanResult(const std::string& filepath, bool threat_detected, const std::string& threat_name = "");
    std::string startSession(const std::string& scan_type);
    void endSession(int files_scanned, int threats_found);
    
    // Add new functions
    int getDurationInMinutes(const ScanSession& session);
    std::string getScanSummary(const std::string& session_id);

private:
    bool connected;
    QSqlDatabase db;
    std::string current_session_id;
    bool initializeDatabase();
    std::string generateSessionId();
};

#endif // DATABASE_H