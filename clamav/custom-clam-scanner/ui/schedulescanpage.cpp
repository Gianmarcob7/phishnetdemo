#include "schedulescanpage.h"
#include "ui_schedulescanpage.h"
#include <QMessageBox>
#include <QDebug>

ScheduleScanPage::ScheduleScanPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleScanPage)
    , scheduler(new ScanScheduler(this))
{
    ui->setupUi(this);
    setupUI();
    loadScheduledScans();
}

ScheduleScanPage::~ScheduleScanPage()
{
    delete ui;
}

void ScheduleScanPage::setupUI()
{
    ui->frequencyComboBox->addItem("Daily", static_cast<int>(ScanInterval::DAILY));
    ui->frequencyComboBox->addItem("Weekly", static_cast<int>(ScanInterval::WEEKLY));
    ui->frequencyComboBox->addItem("Monthly", static_cast<int>(ScanInterval::MONTHLY));

    connect(ui->backButton, &QPushButton::clicked, this, &ScheduleScanPage::onBackButtonClicked);
    connect(ui->scheduleButton, &QPushButton::clicked, this, &ScheduleScanPage::onScheduleButtonClicked);

    updateNextScanLabel();
}

void ScheduleScanPage::loadScheduledScans()
{
    updateNextScanLabel();
}

void ScheduleScanPage::updateNextScanLabel()
{
    ScanInterval interval = static_cast<ScanInterval>(ui->frequencyComboBox->currentData().toInt());
    QDateTime nextScan = scheduler->calculateNextRunTime(interval);
    
    QString nextScanText = QString("Next scan will run at: %1")
                              .arg(nextScan.toString("yyyy-MM-dd hh:mm:ss"));
    ui->nextScanLabel->setText(nextScanText);
}

void ScheduleScanPage::onScheduleButtonClicked()
{
    try {
        ScanInterval interval = static_cast<ScanInterval>(ui->frequencyComboBox->currentData().toInt());
        int scanId = scheduler->scheduleNewScan(ScanType::QUICK, interval, selectedDirectory);
        
        if (scanId != -1) {
            QMessageBox::information(this, "Success", 
                QString("Scan scheduled successfully!\nScan ID: %1\nFrequency: %2")
                    .arg(scanId)
                    .arg(ui->frequencyComboBox->currentText()));
            loadScheduledScans();
        } else {
            QMessageBox::warning(this, "Error", "Failed to schedule scan.");
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in onScheduleButtonClicked:" << e.what();
        QMessageBox::critical(this, "Error", "An error occurred while scheduling the scan.");
    }
}

void ScheduleScanPage::onDeleteScanClicked(int scanId)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete this scheduled scan?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (scheduler->removeScan(scanId)) {
            QMessageBox::information(this, "Success", "Scheduled scan deleted successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete scheduled scan.");
        }
        loadScheduledScans();
    }
}

void ScheduleScanPage::onBackButtonClicked()
{
    emit backButtonClicked();
}

QString ScheduleScanPage::formatScanSchedule(const ScheduledScan* scan)
{
    QString intervalStr;
    switch (scan->interval) {
        case ScanInterval::DAILY:
            intervalStr = "Daily";
            break;
        case ScanInterval::WEEKLY:
            intervalStr = "Weekly";
            break;
        case ScanInterval::MONTHLY:
            intervalStr = "Monthly";
            break;
    }

    QString typeStr;
    switch (scan->type) {
        case ScanType::QUICK:
            typeStr = "Quick Scan";
            break;
        case ScanType::FULL:
            typeStr = "Full Scan";
            break;
        case ScanType::CUSTOM:
            typeStr = "Custom Scan";
            break;
    }

    return QString("%1 - %2\nNext Run: %3")
               .arg(typeStr)
               .arg(intervalStr)
               .arg(scan->nextRunTime.toString("yyyy-MM-dd hh:mm:ss"));
}