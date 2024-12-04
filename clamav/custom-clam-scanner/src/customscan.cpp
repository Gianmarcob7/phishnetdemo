#include "customscan.h"
#include <sys/stat.h>

ClamAVTester::ClamAVTester(const std::string& path) 
    : engine(nullptr), sigs(0), filesScanned(0), threatsFound(0), scanPath(path) {
    memset(&options, 0, sizeof(struct cl_scan_options));
    options.parse = ~0;
    options.general = CL_SCAN_GENERAL_ALLMATCHES;
}

ClamAVTester::~ClamAVTester() {
    if (engine != nullptr) {
        cl_engine_free(engine);
    }
}

bool ClamAVTester::initialize() {
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
    
    return true;
}

void ClamAVTester::setScanPath(const std::string& path) {
    scanPath = path;
}

void ClamAVTester::startScan() {
    if (scanPath.empty()) {
        std::cerr << "Error: No path specified for scanning." << std::endl;
        return;
    }

    if (!initialize()) {
        std::cerr << "Failed to initialize ClamAV" << std::endl;
        return;
    }

    // Reset counters
    filesScanned = 0;
    threatsFound = 0;

    // Determine scan type based on path
    std::string scanType;
    if (std::filesystem::is_directory(scanPath)) {
        scanType = "directory_scan";
    } else {
        scanType = "file_scan";
    }

    // Start new database session
    database.startSession(scanType);

    std::cout << "\nStarting scan of: " << scanPath << std::endl;

    try {
        if (!std::filesystem::exists(scanPath)) {
            std::cout << "Error: Path does not exist: " << scanPath << std::endl;
            return;
        }

        if (std::filesystem::is_directory(scanPath)) {
            std::cout << "Scanning directory..." << std::endl;
            scanDirectory(scanPath);
        } else if (std::filesystem::is_regular_file(scanPath)) {
            std::cout << "Scanning file..." << std::endl;
            scanFile(scanPath);
        } else {
            std::cout << "Error: Path is neither a regular file nor a directory." << std::endl;
            return;
        }

        // End database session with scan results
        database.endSession(filesScanned, threatsFound);

        std::cout << "\nScan completed." << std::endl;
        std::cout << "Files scanned: " << filesScanned << std::endl;
        std::cout << "Threats found: " << threatsFound << std::endl;

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error during scan: " << e.what() << std::endl;
        // End session even if there was an error
        database.endSession(filesScanned, threatsFound);
    }
}

bool ClamAVTester::scanFile(const std::string& filepath) {
    const char* virname = nullptr;
    unsigned long int scanned = 0;
    cl_error_t ret;
    
    filesScanned++;
    if (filesScanned % 100 == 0) {
        std::cout << "\rFiles scanned: " << filesScanned << std::flush;
    }
    
    ret = cl_scanfile(filepath.c_str(), &virname, &scanned, engine, &options);
    
    switch (ret) {
        case CL_CLEAN:
            // Log clean file to database
            database.logScanResult(filepath, false);
            return true;
            
        case CL_VIRUS:
            std::cout << "\n[!] Threat detected in: " << filepath 
                     << "\n[!] Threat name: " << virname << std::endl;
            // Log infected file to database with threat name
            database.logScanResult(filepath, true, virname);
            threatsFound++;
            quarantineFile(filepath);
            return false;
            
        default:
            std::cout << "\nError scanning file " << filepath 
                     << ": " << cl_strerror(ret) << std::endl;
            // Log error as a failed scan
            database.logScanResult(filepath, false, "scan_error");
            return false;
    }
}

void ClamAVTester::scanDirectory(const std::string& dirpath) {
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(dirpath)) {
            if (std::filesystem::is_regular_file(entry)) {
                scanFile(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
}

void ClamAVTester::quarantineFile(const std::string& filepath) {
    try {
        // Create quarantine directory if it doesn't exist
        std::filesystem::create_directories(quarantinePath);
        
        // Construct the destination path
        std::string filename = std::filesystem::path(filepath).filename().string();
        std::string destination = (std::filesystem::path(quarantinePath) / filename).string();
        
        
        std::filesystem::rename(filepath, destination);
        std::cout << "File successfully moved to quarantine: " << destination << std::endl;
        
        // Log quarantine action to database
        // database.logScanResult(destination, true, "quarantined");
        
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error moving file to quarantine: " << e.what() << std::endl;
    }
}