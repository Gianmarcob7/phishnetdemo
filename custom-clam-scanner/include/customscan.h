#ifndef CUSTOMSCAN_H
#define CUSTOMSCAN_H

#include <iostream>
#include <cstdlib>
#include <clamav.h>
#include <string>
#include <sstream>
#include <memory>
#include <array>
#include <iomanip>
#include <filesystem>
#include "Database.h"

// Handles virus scanning using ClamAV. Remember to call initialize() first
class ClamAVTester {
public:  
   // Stats tracking for the current scan
   int filesScanned;
   int threatsFound; 
   std::string scanPath;

   explicit ClamAVTester(const std::string& path = "");
   ~ClamAVTester();
   
   bool initialize(); 
   bool scanFile(const std::string& filepath);
   void scanDirectory(const std::string& dirpath);
   // Moves infected files to quarantine - needs write permissions
   void quarantineFile(const std::string& filepath); 
   void startScan();
   void setScanPath(const std::string& path);

private:
   // ClamAV engine instance - cleaned up in destructor
   cl_engine* engine;
   unsigned int sigs;
   struct cl_scan_options options;
   Database database;
   const std::string quarantinePath = "/home/gianmarco/Downloads/clamav/clamav/custom-clam-scanner/build/Quarantine";
};

#endif