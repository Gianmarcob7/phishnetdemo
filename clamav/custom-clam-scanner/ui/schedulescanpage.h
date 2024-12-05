#ifndef SCHEDULESCANPAGE_H
#define SCHEDULESCANPAGE_H

#include <QWidget>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include "scheduler.h"

namespace Ui {
class ScheduleScanPage;
}

class ScheduleScanPage : public QWidget {
    Q_OBJECT

public:
    explicit ScheduleScanPage(QWidget *parent = nullptr);
    ~ScheduleScanPage();

private slots:
    void onBackButtonClicked();
    void onScheduleButtonClicked();
    void checkScheduledScans();
    void onScanTypeChanged(int index);
    void onFrequencyChanged(int index);

signals:
    void backButtonClicked();
    void startScan(const QString& scanType, const QString& customPath = QString(), ScanInterval interval = ScanInterval::DAILY);

private:
    Ui::ScheduleScanPage *ui;
    QTimer* scheduleTimer;
    QString selectedScanType;
    QString customScanPath;
    ScanInterval selectedInterval;
    QDateTime nextScanTime;
    std::unique_ptr<ScanScheduler> scheduler;
    
    void setupUI();
    void setupConnections();
};

#endif // SCHEDULESCANPAGE_H