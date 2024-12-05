#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QMap>
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

class ScheduledScan : public QObject {
    Q_OBJECT
public:
    explicit ScheduledScan(QObject* parent = nullptr);
    ~ScheduledScan();

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

    int scheduleNewScan(ScanType type, ScanInterval interval, const QDateTime& runTime, const QString& path);
    bool removeScan(int scanId);
    QMap<int, ScheduledScan*> getScheduledScans() const { return scheduledScans; }

private slots:
    void executeScan(int scanId);

private:
    QMap<int, ScheduledScan*> scheduledScans;
    int nextScanId;
    std::unique_ptr<SystemScan> systemScanner;

    QDateTime calculateNextRunTime(ScanInterval interval, const QDateTime& currentTime) const;
    void setupTimer(ScheduledScan* scan);
    qint64 getIntervalMilliseconds(ScanInterval interval) const;
    void cleanupScan(ScheduledScan* scan);
};

#endif // SCHEDULER_H