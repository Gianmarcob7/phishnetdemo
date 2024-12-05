// ScanWorker.cpp
#include "ScanWorker.h"
#include <iostream>

ScanWorker::ScanWorker(QObject* parent) 
    : QObject(parent)
    , customScanner(nullptr)
    , systemScanner(nullptr)
    , quickScanner(nullptr)
{
}

ScanWorker::~ScanWorker()
{
    if (quickScanner) delete quickScanner;
    if (systemScanner) delete systemScanner;
    if (customScanner) delete customScanner;
}

void ScanWorker::setScanPath(const QString& path)
{
    scanPath = path;
}

void ScanWorker::setScanType(const QString& type)
{
    scanType = type;
}

void ScanWorker::doScan()
{
    if (scanType == "quick") {
        std::cout << "Starting quick scan..." << std::endl;
        quickScanner = new QuickScan();
        if (!quickScanner) {
            std::cout << "Failed to create QuickScan object" << std::endl;
            return;
        }
        std::cout << "Created QuickScan object successfully" << std::endl;
        
        quickScanner->startScan();
        emit scanProgress(quickScanner->getFilesScanned());
        
        std::cout << "Scan completed. Files scanned: " << quickScanner->getFilesScanned() 
                  << " Threats: " << quickScanner->getThreatsFound() << std::endl;
        
        emit scanComplete(quickScanner->getFilesScanned(), quickScanner->getThreatsFound());
        delete quickScanner;
        quickScanner = nullptr;
    }
    else if (scanType == "system") {
        systemScanner = new SystemScan();
        systemScanner->startScan();
        emit scanComplete(systemScanner->getFilesScanned(), systemScanner->getThreatsFound());
        delete systemScanner;
        systemScanner = nullptr;
    }
    else if (scanType == "custom") {
        customScanner = new ClamAVTester(scanPath.toStdString());
        customScanner->startScan();
        emit scanComplete(customScanner->filesScanned, customScanner->threatsFound);
        delete customScanner;
        customScanner = nullptr;
    }
}