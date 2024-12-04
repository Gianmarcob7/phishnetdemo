// include/scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <map>
#include <memory>
#include "systemscan.h"

enum class ScanInterval {
    DAILY = 0,
    WEEKLY = 1,
    MONTHLY = 2  // Changed from BIWEEKLY to MONTHLY
};

enum class ScanType {
    QUICK,
    FULL,
    CUSTOM
};

struct ScheduledScan {
    int id;
    ScanType type;
    ScanInterval interval;
    QString path;
    QDateTime nextRunTime;
    QTimer* timer;
};

class ScanScheduler : public QObject {
    Q_OBJECT

public:
    explicit ScanScheduler(QObject* parent = nullptr);
    ~ScanScheduler();

    int scheduleNewScan(ScanType type, ScanInterval interval, const QString& path);
    bool removeScan(int scanId);
    QDateTime calculateNextRunTime(ScanInterval interval) const;

private slots:
    void executeScan(int scanId);

private:
    std::map<int, std::unique_ptr<ScheduledScan>> scheduledScans;
    int nextScanId;
    
    void setupTimer(ScheduledScan* scan);
    qint64 getIntervalMilliseconds(ScanInterval interval) const;
};

#endif // SCHEDULER_H

// src/scheduler.cpp
#include "scheduler.h"
#include <QDebug>

ScanScheduler::ScanScheduler(QObject* parent)
    : QObject(parent)
    , nextScanId(1)
{
}

ScanScheduler::~ScanScheduler() {
    for (auto& pair : scheduledScans) {
        if (pair.second->timer) {
            pair.second->timer->stop();
            delete pair.second->timer;
        }
    }
}

int ScanScheduler::scheduleNewScan(ScanType type, ScanInterval interval, const QString& path) {
    try {
        auto scan = std::make_unique<ScheduledScan>();
        scan->id = nextScanId++;
        scan->type = type;
        scan->interval = interval;
        scan->path = path;
        scan->nextRunTime = calculateNextRunTime(interval);
        scan->timer = new QTimer(this);

        setupTimer(scan.get());
        
        int scanId = scan->id;
        scheduledScans[scanId] = std::move(scan);
        
        return scanId;
    }
    catch (const std::exception& e) {
        qDebug() << "Error scheduling scan:" << e.what();
        return -1;
    }
}

bool ScanScheduler::removeScan(int scanId) {
    auto it = scheduledScans.find(scanId);
    if (it != scheduledScans.end()) {
        if (it->second->timer) {
            it->second->timer->stop();
            delete it->second->timer;
        }
        scheduledScans.erase(it);
        return true;
    }
    return false;
}

void ScanScheduler::executeScan(int scanId) {
    auto it = scheduledScans.find(scanId);
    if (it != scheduledScans.end()) {
        try {
            // Create and execute the scan based on type
            if (it->second->type == ScanType::QUICK) {
                SystemScan scanner;
                scanner.scanDirectory("/home");
            }
            else if (it->second->type == ScanType::CUSTOM && !it->second->path.isEmpty()) {
                SystemScan scanner;
                scanner.scanDirectory(it->second->path.toStdString());
            }
            else {
                // Full system scan
                SystemScan scanner;
                scanner.startScan();
            }
            
            // Update next run time
            it->second->nextRunTime = calculateNextRunTime(it->second->interval);
            setupTimer(it->second.get());
        }
        catch (const std::exception& e) {
            qDebug() << "Error executing scan:" << e.what();
        }
    }
}

QDateTime ScanScheduler::calculateNextRunTime(ScanInterval interval) const {
    QDateTime now = QDateTime::currentDateTime();
    
    switch (interval) {
        case ScanInterval::DAILY:
            return now.addDays(1);
        
        case ScanInterval::WEEKLY:
            return now.addDays(7);
        
        case ScanInterval::MONTHLY:  // Changed from BIWEEKLY
            return now.addMonths(1);
        
        default:
            return now;
    }
}

void ScanScheduler::setupTimer(ScheduledScan* scan) {
    if (!scan->timer) return;
    
    // Disconnect any existing connections
    disconnect(scan->timer, nullptr, this, nullptr);
    
    // Calculate initial delay
    qint64 initialDelay = QDateTime::currentDateTime().msecsTo(scan->nextRunTime);
    
    // Setup timer
    scan->timer->setSingleShot(true);
    connect(scan->timer, &QTimer::timeout, this, [this, id = scan->id]() {
        executeScan(id);
    });
    
    // Start timer
    if (initialDelay > 0) {
        scan->timer->start(initialDelay);
    }
}

qint64 ScanScheduler::getIntervalMilliseconds(ScanInterval interval) const {
    switch (interval) {
        case ScanInterval::DAILY:
            return qint64(24) * 60 * 60 * 1000; // 24 hours
        
        case ScanInterval::WEEKLY:
            return qint64(7) * 24 * 60 * 60 * 1000; // 7 days
        
        case ScanInterval::MONTHLY:
            return qint64(30) * 24 * 60 * 60 * 1000; // 30 days
        
        default:
            return qint64(24) * 60 * 60 * 1000; // Default to daily
    }
}