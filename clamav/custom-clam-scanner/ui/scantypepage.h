#ifndef SCANTYPEPAGE_H
#define SCANTYPEPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QThread>
#include <QDateTime>
#include <QTimer>
#include "ScanWorker.h"
#include <QVBoxLayout>

namespace Ui {
class ScanTypePage;
}

class ScanTypePage : public QWidget
{
    Q_OBJECT

public:
    explicit ScanTypePage(QWidget *parent = nullptr);
    ~ScanTypePage();

private slots:
    void onBackButtonClicked();
    void onScanTypeChanged(int index);
    void onBrowseButtonClicked();
    void onCustomScanButtonClicked();
    void startQuickScan();
    void startSystemScan();
    void startCustomScan();
    void handleScanComplete(int filesScanned, int threatsFound);
    void updateScanProgress(int filesScanned);
    void checkScheduledScans();

signals:
    void backButtonClicked();
    void startScan();

private:
    Ui::ScanTypePage *ui;
    QString selectedDirectory;
    QThread* scanThread;
    ScanWorker* worker;
    void setupScanWorker();
    void setMessageBoxStyle(QMessageBox* msgBox);
    
    // Scheduling related members
    QTimer* scheduleTimer;
    QDateTime scheduledScanTime;
    QString scheduledScanType;
    void setupScheduler();
};

#endif // SCANTYPEPAGE_H