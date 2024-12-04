#ifndef SCHEDULESCANPAGE_H
#define SCHEDULESCANPAGE_H

#include <QWidget>
#include "../include/scheduler.h"
class ScheduledScan;

namespace Ui {
class ScheduleScanPage;
}

class ScheduleScanPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleScanPage(QWidget *parent = nullptr);
    ~ScheduleScanPage();

private slots:
    void onBackButtonClicked();
    void onScheduleButtonClicked();
    void onDeleteScanClicked(int scanId);

signals:
    void backButtonClicked();

private:
    Ui::ScheduleScanPage *ui;
    ScanScheduler* scheduler;
    QString selectedDirectory;
    
    void setupUI();
    void loadScheduledScans();
    void updateNextScanLabel();
    QString formatScanSchedule(const ScheduledScan* scan);
};

#endif // SCHEDULESCANPAGE_H