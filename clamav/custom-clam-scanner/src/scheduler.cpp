#include "scheduler.h"
#include <QDebug>

ScanScheduler::ScanScheduler(QObject* parent)
    : QObject(parent)
    , nextScanId(1)
{
}

ScanScheduler::~ScanScheduler() 
{
    for (auto& pair : scheduledScans) {
        if (pair.second->timer) {
            pair.second->timer->stop();
            delete pair.second->timer;
        }
    }
}

int ScanScheduler::scheduleNewScan(ScanType type, ScanInterval interval, const QString& path) 
{
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

bool ScanScheduler::removeScan(int scanId) 
{
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

void ScanScheduler::executeScan(int scanId) 
{
    auto it = scheduledScans.find(scanId);
    if (it != scheduledScans.end()) {
        try {
            SystemScan scanner;
            scanner.startScan();
            
            it->second->nextRunTime = calculateNextRunTime(it->second->interval);
            setupTimer(it->second.get());
        }
        catch (const std::exception& e) {
            qDebug() << "Error executing scan:" << e.what();
        }
    }
}

QDateTime ScanScheduler::calculateNextRunTime(ScanInterval interval) const 
{
    QDateTime now = QDateTime::currentDateTime();
    
    switch (interval) {
        case ScanInterval::DAILY:
            return now.addDays(1);
        case ScanInterval::WEEKLY:
            return now.addDays(7);
        case ScanInterval::MONTHLY:
            return now.addMonths(1);
        default:
            return now;
    }
}

void ScanScheduler::setupTimer(ScheduledScan* scan) 
{
    if (!scan->timer) return;
    
    disconnect(scan->timer, nullptr, this, nullptr);
    
    qint64 initialDelay = QDateTime::currentDateTime().msecsTo(scan->nextRunTime);
    
    scan->timer->setSingleShot(true);
    connect(scan->timer, &QTimer::timeout, this, [this, id = scan->id]() {
        executeScan(id);
    });
    
    if (initialDelay > 0) {
        scan->timer->start(initialDelay);
    }
}

qint64 ScanScheduler::getIntervalMilliseconds(ScanInterval interval) const 
{
    switch (interval) {
        case ScanInterval::DAILY:
            return qint64(24) * 60 * 60 * 1000;
        case ScanInterval::WEEKLY:
            return qint64(7) * 24 * 60 * 60 * 1000;
        case ScanInterval::MONTHLY:
            return qint64(30) * 24 * 60 * 60 * 1000;
        default:
            return qint64(24) * 60 * 60 * 1000;
    }
}