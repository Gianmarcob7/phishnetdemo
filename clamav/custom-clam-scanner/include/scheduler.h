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
    MONTHLY = 2
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