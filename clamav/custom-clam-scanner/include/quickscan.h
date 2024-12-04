#ifndef QUICKSCAN_H
#define QUICKSCAN_H

#include <iostream>
#include <cstdlib>
#include <clamav.h>
#include <string>
#include <filesystem>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Database.h"
#include <pwd.h>
#include <unistd.h>

namespace fs = std::filesystem;

class QuickScan {
private:
    cl_engine* engine;
    unsigned int sigs;
    struct cl_scan_options options;
    Database database;
    int filesScanned;
    int threatsFound;
    std::chrono::steady_clock::time_point lastUpdateTime;
    
    std::vector<std::string> rootDirs;  // Directories to scan
    
    bool initializeClamAV();
    bool scanFile(const std::string& filepath);
    void scanDirectory(const fs::path& path);
    void quarantineFile(const std::string& filepath);
    const std::string quarantinePath = "/home/gianmarco/Downloads/clamav/clamav/custom-clam-scanner/build/Quarantine";

public:
    QuickScan();
    ~QuickScan();
    void startScan();
    int getFilesScanned() const { return filesScanned; }
    int getThreatsFound() const { return threatsFound; }
};

#endif