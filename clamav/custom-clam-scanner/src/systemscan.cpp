//systemscan.cpp
#include "systemscan.h"
#include <filesystem>
#include <chrono>

// Initialize system scanner with default paths and settings
SystemScan::SystemScan() 
   : engine(nullptr), filesScanned(0), threatsFound(0) {
   lastUpdateTime = std::chrono::steady_clock::now();
   
   // Key system directories to scan
   rootDirs = {
       "/home",
       "/usr",
       "/opt"
   };
   
   // System directories that don't need scanning
   skipDirs = {
       "/proc",
       "/sys",
       "/dev",
       "/run",
       "/mnt",
       "/media",
       "/tmp"
   };
}

// Clean up ClamAV engine
SystemScan::~SystemScan() {
   if (engine != nullptr) {
       cl_engine_free(engine);
   }
}

// Check if directory should be skipped
bool SystemScan::shouldSkipDirectory(const std::string& path) {
   return std::any_of(skipDirs.begin(), skipDirs.end(),
       [&path](const std::string& skipDir) {
           return path.find(skipDir) == 0;
       });
}

// Initialize ClamAV scanning engine
bool SystemScan::initializeClamAV() {
   cl_error_t ret;
   
   ret = cl_init(CL_INIT_DEFAULT);
   if (ret != CL_SUCCESS) {
       std::cerr << "Failed to initialize libclamav: " << cl_strerror(ret) << std::endl;
       return false;
   }
   
   engine = cl_engine_new();
   if (engine == nullptr) {
       std::cerr << "Failed to create new engine" << std::endl;
       return false;
   }
   
   // Load virus database
   ret = cl_load(cl_retdbdir(), engine, &sigs, CL_DB_STDOPT);
   if (ret != CL_SUCCESS) {
       std::cerr << "Failed to load virus database: " << cl_strerror(ret) << std::endl;
       cl_engine_free(engine);
       return false;
   }
   
   ret = cl_engine_compile(engine);
   if (ret != CL_SUCCESS) {
       std::cerr << "Engine compilation failed: " << cl_strerror(ret) << std::endl;
       cl_engine_free(engine);
       return false;
   }

   // Set scan options
   memset(&options, 0, sizeof(struct cl_scan_options));
   options.parse = ~0;
   options.general = CL_SCAN_GENERAL_ALLMATCHES;
   
   return true;
}

// Move infected file to quarantine
void SystemScan::quarantineFile(const std::string& filepath) {
   try {
       fs::create_directories(quarantinePath);
       
       std::string filename = fs::path(filepath).filename().string();
       std::string destination = (fs::path(quarantinePath) / filename).string();
       
       fs::rename(filepath, destination);
       std::cout << "File successfully moved to quarantine: " << destination << std::endl;
       
       database.logScanResult(destination, true, "quarantined");
       
   } catch (const fs::filesystem_error& e) {
       std::cerr << "Error moving file to quarantine: " << e.what() << std::endl;
   }
}

// Scan individual file for threats
bool SystemScan::scanFile(const std::string& filepath) {
   const char* virname = nullptr;
   unsigned long int scanned = 0;
   cl_error_t ret;

   filesScanned++;
   
   // Update progress display every 2 seconds
   auto now = std::chrono::steady_clock::now();
   if (std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdateTime).count() >= 2) {
       std::cout << "\rFiles scanned: " << filesScanned << " | Threats found: " << threatsFound << std::flush;
       lastUpdateTime = now;
   }
   
   ret = cl_scanfile(filepath.c_str(), &virname, &scanned, engine, &options);
   
   switch (ret) {
       case CL_CLEAN:
           database.logScanResult(filepath, false);
           return true;
           
       case CL_VIRUS:
           std::cout << "\n[!] Threat detected in: " << filepath 
                    << "\n[!] Threat name: " << virname << std::endl;
           database.logScanResult(filepath, true, virname);
           threatsFound++;
           quarantineFile(filepath);
           return false;
           
       default:
           std::cerr << "\nError scanning file " << filepath 
                    << ": " << cl_strerror(ret) << std::endl;
           database.logScanResult(filepath, false, "scan_error");
           return false;
   }
}

// Recursively scan directory and its contents
void SystemScan::scanDirectory(const fs::path& path) {
   if (shouldSkipDirectory(path.string())) {
       return;
   }

   try {
       for (const auto& entry : fs::recursive_directory_iterator(
           path,
           fs::directory_options::skip_permission_denied
       )) {
           if (fs::is_regular_file(entry)) {
               scanFile(entry.path().string());
           }
       }
   } catch (const fs::filesystem_error& e) {
       std::cerr << "Error accessing directory: " << e.what() << std::endl;
   }
}

// Main scanning function - scans all configured system directories
void SystemScan::startScan() {
   auto start_time = std::chrono::steady_clock::now();

   std::cout << "=== System Scan Starting ===\n";
   std::cout << "This may take a while...\n\n";
   
   database.startSession("system");

   if (!initializeClamAV()) {
       std::cerr << "Scanner initialization failed\n";
       return;
   }

   // Scan each root directory
   for (const auto& rootDir : rootDirs) {
       if (fs::exists(rootDir)) {
           scanDirectory(rootDir);
       }
   }

   auto end_time = std::chrono::steady_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time);

   database.endSession(filesScanned, threatsFound);

   // Display scan results
   std::cout << "\n\nSystem Scan Summary:\n";
   std::cout << "------------------\n";
   std::cout << "Duration: " << duration.count() << " minutes\n";
   std::cout << "Files Scanned: " << filesScanned << "\n";
   if (threatsFound > 0) {
       std::cout << "Threats Detected: " << threatsFound << "\n";
       std::cout << "Threats have been moved to: " << quarantinePath << std::endl;
   } else {
       std::cout << "No Threats Detected" << std::endl;
   }
}