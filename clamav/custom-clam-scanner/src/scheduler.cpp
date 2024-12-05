#include "scheduler.h"
#include <QDebug>

ScheduledScan::ScheduledScan(QObject* parent)
    : QObject(parent)
    , id(-1)
    , timer(nullptr)
{
}

ScheduledScan::~ScheduledScan() {
    delete timer;
}

ScanScheduler::ScanScheduler(QObject* parent)
    : QObject(parent)
    , nextScanId(1)
    , systemScanner(std::make_unique<SystemScan>())
{
}

ScanScheduler::~ScanScheduler() {
    qDeleteAll(scheduledScans);
    scheduledScans.clear();
}

int ScanScheduler::scheduleNewScan(ScanType type, ScanInterval interval, const QDateTime& runTime, const QString& path) {
    try {
        auto* scan = new ScheduledScan(this);
        scan->id = nextScanId++;
        scan->type = type;
        scan->interval = interval;
        scan->path = path;
        scan->nextRunTime = runTime;
        scan->timer = new QTimer(scan);

        scheduledScans[scan->id] = scan;
        setupTimer(scan);

        qDebug() << "Scheduled new scan with ID:" << scan->id;
        return scan->id;
    } catch (const std::exception& e) {
        qDebug() << "Error scheduling scan:" << e.what();
        return -1;
    }
}

bool ScanScheduler::removeScan(int scanId) {
    if (scheduledScans.contains(scanId)) {
        auto* scan = scheduledScans.take(scanId);
        delete scan;
        return true;
    }
    return false;
}

void ScanScheduler::executeScan(int scanId) {
    if (auto it = scheduledScans.find(scanId); it != scheduledScans.end()) {
        auto* scan = it.value();
        
        try {
            if (scan->path.isEmpty()) {
                systemScanner->startScan();
            } else {
                systemScanner->scanDirectory(scan->path.toStdString());
            }

            qDebug() << "Scan completed - ID:" << scanId
                     << "Files scanned:" << systemScanner->getFilesScanned()
                     << "Threats found:" << systemScanner->getThreatsFound();

            // Update next run time
            scan->nextRunTime = calculateNextRunTime(scan->interval, scan->nextRunTime);
            
        } catch (const std::exception& e) {
            qDebug() << "Error executing scan:" << e.what();
        }
    }
}

QDateTime ScanScheduler::calculateNextRunTime(ScanInterval interval, const QDateTime& currentTime) const {
    QDateTime nextRun = currentTime;

    switch (interval) {
        case ScanInterval::DAILY:
            nextRun = nextRun.addDays(1);
            break;
        case ScanInterval::WEEKLY:
            nextRun = nextRun.addDays(7);
            break;
        case ScanInterval::MONTHLY:
            nextRun = nextRun.addMonths(1);
            break;
    }

    return nextRun;
}

void ScanScheduler::setupTimer(ScheduledScan* scan) {
    if (!scan || !scan->timer) return;

    connect(scan->timer, &QTimer::timeout, this, [this, scanId = scan->id]() {
        executeScan(scanId);
    });

    qint64 interval = getIntervalMilliseconds(scan->interval);
    scan->timer->start(interval);
}

qint64 ScanScheduler::getIntervalMilliseconds(ScanInterval interval) const {
    switch (interval) {
        case ScanInterval::DAILY:
            return 24 * 60 * 60 * 1000; // 24 hours
        case ScanInterval::WEEKLY:
            return 7 * 24 * 60 * 60 * 1000; // 7 days
        case ScanInterval::MONTHLY:
            return 30 * 24 * 60 * 60 * 1000; // 30 days (approximate)
    }
    return 24 * 60 * 60 * 1000; // Default to daily
}

void ScanScheduler::cleanupScan(ScheduledScan* scan) {
    if (scan) {
        if (scan->timer) {
            scan->timer->stop();
        }
        delete scan;
    }
}