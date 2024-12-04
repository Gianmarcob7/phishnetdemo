#include "quickscan.h"
#include <filesystem>
#include <chrono>

QuickScan::QuickScan() 
    : engine(nullptr), filesScanned(0), threatsFound(0) {
    lastUpdateTime = std::chrono::steady_clock::now();
    
    // Get the real user's home directory even when running as root
    const char* sudoUser = getenv("SUDO_USER");
    std::string homeDir;
    
    if (sudoUser) {
        // If running with sudo, get the real user's home
        struct passwd *pw = getpwnam(sudoUser);
        if (pw) {
            homeDir = pw->pw_dir;
        }
    } else {
        // Normal user execution
        const char* home = getenv("HOME");
        if (home) {
            homeDir = home;
        }
    }
    
    // Fallback if we couldn't get the home directory
    if (homeDir.empty()) {
        std::cerr << "Could not determine home directory" << std::endl;
        homeDir = "/home";
    }
    
    std::cout << "Using home directory: " << homeDir << std::endl;
    
    rootDirs = {
        homeDir + "/Downloads",
        homeDir + "/Desktop",
        homeDir + "/Documents"
    };
}

QuickScan::~QuickScan() {
    if (engine != nullptr) {
        cl_engine_free(engine);
    }
}

bool QuickScan::initializeClamAV() {
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

    memset(&options, 0, sizeof(struct cl_scan_options));
    options.parse = ~0;
    options.general = CL_SCAN_GENERAL_ALLMATCHES;
    
    return true;
}

void QuickScan::quarantineFile(const std::string& filepath) {
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

bool QuickScan::scanFile(const std::string& filepath) {
    const char* virname = nullptr;
    unsigned long int scanned = 0;
    cl_error_t ret;

    filesScanned++;
    
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

void QuickScan::scanDirectory(const fs::path& path) {
    try {
        std::cout << "Scanning directory: " << path << std::endl;
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

void QuickScan::startScan() {
    auto start_time = std::chrono::steady_clock::now();

    std::cout << "=== Quick Scan Starting ===\n";
    std::cout << "Scanning user directories for threats...\n\n";
    
    database.startSession("quick");

    if (!initializeClamAV()) {
        std::cerr << "Scanner initialization failed\n";
        return;
    }

    for (const auto& rootDir : rootDirs) {
        if (fs::exists(rootDir)) {
            std::cout << "Scanning location: " << rootDir << std::endl;
            scanDirectory(rootDir);
        } else {
            std::cout << "Directory does not exist: " << rootDir << std::endl;
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    database.endSession(filesScanned, threatsFound);

    std::cout << "\n\nQuick Scan Summary:\n";
    std::cout << "------------------\n";
    std::cout << "Duration: " << duration.count() << " seconds\n";
    std::cout << "Files Scanned: " << filesScanned << "\n";
    if (threatsFound > 0) {
        std::cout << "Threats Detected: " << threatsFound << "\n";
        std::cout << "Threats have been moved to: " << quarantinePath << std::endl;
    } else {
        std::cout << "No Threats Detected" << std::endl;
    }
}