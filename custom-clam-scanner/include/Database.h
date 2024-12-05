#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <filesystem>

// Stores details about individual file scans
struct ScanRecord {
   std::string file_path;    // Path of scanned file
   bool detected;            
   std::string scan_date;    
   std::string threat_name;  
};

// Tracks overall scan session info and stats
struct ScanSession {
   std::string session_id;    
   std::string scan_type;     
   std::string start_time;    
   std::string end_time;     
   int files_scanned;         
   int threats_found;         // Total number of threats detected
};

// Handles all database operations for storing scan results
class Database {
private:
   sqlite3* db;                      // Main database connection
   std::string current_session_id;   // Tracks active scan session
   
   // Core database setup and utilities
   void createTables();              // Sets up DB schema if needed
   std::string generateSessionId();  // Creates unique session ID
   std::string getCurrentTimestamp();
   void generateReport(const std::string& session_id); 

public:
   Database();  
   ~Database(); 
   
   // Session lifecycle methods
   void startSession(const std::string& scan_type);
   void endSession(int files_scanned, int threats_found);
   
   // Record scanning results
   void logScanResult(const std::string& filePath, bool detected, const std::string& threatName = "");
   
   // Query scan history and generate reports
   std::vector<ScanSession> getRecentSessions(int limit = 10);
   std::vector<ScanRecord> getSessionResults(const std::string& session_id);
   std::string getScanSummary(const std::string& session_id);
   int getDurationInMinutes(const ScanSession& session);
   void viewScanHistory();
};

#endif