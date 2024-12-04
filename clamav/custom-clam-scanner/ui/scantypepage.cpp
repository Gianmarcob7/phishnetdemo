// schedulescanpage.cpp
#include "schedulescanpage.h"
#include "ui_schedulescanpage.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include <QTime>

ScheduleScanPage::ScheduleScanPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleScanPage)
    , scheduler(new ScanScheduler())
    , selectedDirectory("")
{
    try {
        ui->setupUi(this);
        setupUI();
        loadScheduledScans();
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in ScheduleScanPage constructor:" << e.what();
    }
}

ScheduleScanPage::~ScheduleScanPage()
{
    try {
        delete scheduler;
        delete ui;
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in ScheduleScanPage destructor:" << e.what();
    }
}

void ScheduleScanPage::setupUI()
{
    // Set up frequency combo box with updated intervals
    ui->frequencyComboBox->addItem("Daily", static_cast<int>(ScanInterval::DAILY));
    ui->frequencyComboBox->addItem("Weekly", static_cast<int>(ScanInterval::WEEKLY));
    ui->frequencyComboBox->addItem("Monthly", static_cast<int>(ScanInterval::MONTHLY));

    // Connect signals
    connect(ui->backButton, &QPushButton::clicked, this, &ScheduleScanPage::onBackButtonClicked);
    connect(ui->scheduleButton, &QPushButton::clicked, this, &ScheduleScanPage::onScheduleButtonClicked);

    // Setup initial state
    updateNextScanLabel();
}

void ScheduleScanPage::loadScheduledScans()
{
    // This function would load any previously scheduled scans
    // For now, we just update the next scan label
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
        
        // Schedule the scan
        int scanId = scheduler->scheduleNewScan(ScanType::QUICK, interval, selectedDirectory);
        
        if (scanId != -1) {
            QString message = QString("Scan scheduled successfully!\n\n"
                                   "Scan ID: %1\n"
                                   "Type: Quick Scan\n"
                                   "Frequency: %2\n")
                                .arg(scanId)
                                .arg(ui->frequencyComboBox->currentText());

            QMessageBox* msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Success");
            msgBox->setText(message);
            msgBox->setIcon(QMessageBox::Information);
            msgBox->exec();
            delete msgBox;

            // Update UI
            loadScheduledScans();
        } else {
            QMessageBox* msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Error");
            msgBox->setText("Failed to schedule scan. Please try again.");
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->exec();
            delete msgBox;
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in onScheduleButtonClicked:" << e.what();
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Error");
        msgBox->setText("An error occurred while scheduling the scan.");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->exec();
        delete msgBox;
    }
}

void ScheduleScanPage::onDeleteScanClicked(int scanId)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Confirm Delete",
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

// This helper method could be used to format the display of scan schedules
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
}s