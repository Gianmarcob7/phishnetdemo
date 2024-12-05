#include "schedulescanpage.h"
#include "ui_schedulescanpage.h"
#include <QMessageBox>
#include <QDateTime>

ScheduleScanPage::ScheduleScanPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleScanPage)
    , scheduleTimer(nullptr)
    , scheduler(std::make_unique<ScanScheduler>(this))
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
}

ScheduleScanPage::~ScheduleScanPage() {
    if (scheduleTimer) {
        scheduleTimer->stop();
        delete scheduleTimer;
    }
    delete ui;
}

void ScheduleScanPage::setupUI() {
    // Setup scan type combo box
    ui->scanTypeComboBox->addItem("Quick Scan", "quick");
    ui->scanTypeComboBox->addItem("System Scan", "system");
    ui->scanTypeComboBox->addItem("Custom Scan", "custom");

    // Setup scan frequency combo box
    ui->frequencyComboBox->addItem("Daily", static_cast<int>(ScanInterval::DAILY));
    ui->frequencyComboBox->addItem("Weekly", static_cast<int>(ScanInterval::WEEKLY));
    ui->frequencyComboBox->addItem("Monthly", static_cast<int>(ScanInterval::MONTHLY));

    // Setup scan time combo boxes
    for (int i = 0; i < 24; i++) {
        QString hourStr = QString("%1").arg(i, 2, 10, QChar('0'));
        ui->hourComboBox->addItem(hourStr);
    }
    for (int i = 0; i < 60; i += 15) {
        QString minuteStr = QString("%1").arg(i, 2, 10, QChar('0'));
        ui->minuteComboBox->addItem(minuteStr);
    }

    // Initialize timer
    scheduleTimer = new QTimer(this);
    scheduleTimer->start(60000); // Check every minute
}

void ScheduleScanPage::setupConnections() {
    connect(ui->backButton, &QPushButton::clicked, this, &ScheduleScanPage::onBackButtonClicked);
    connect(ui->scanTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ScheduleScanPage::onScanTypeChanged);
    connect(ui->frequencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ScheduleScanPage::onFrequencyChanged);
    connect(scheduleTimer, &QTimer::timeout, this, &ScheduleScanPage::checkScheduledScans);
    connect(ui->scheduleButton, &QPushButton::clicked, this, &ScheduleScanPage::onScheduleButtonClicked);
}

void ScheduleScanPage::onBackButtonClicked() {
    emit backButtonClicked();
}

void ScheduleScanPage::onScheduleButtonClicked() {
    ScanType selectedType = static_cast<ScanType>(ui->scanTypeComboBox->currentData().toInt());
    selectedInterval = static_cast<ScanInterval>(ui->frequencyComboBox->currentData().toInt());
    int selectedHour = ui->hourComboBox->currentIndex();
    int selectedMinute = ui->minuteComboBox->currentIndex() * 15;

    QDateTime scheduleTime = QDateTime::currentDateTime().addSecs(selectedHour * 3600 + selectedMinute * 60);

    int scanId = scheduler->scheduleNewScan(selectedType, selectedInterval, scheduleTime, customScanPath);
    if (scanId != -1) {
        QString message = QString("Scan scheduled for %1\nType: %2\nFrequency: %3")
                             .arg(scheduler->getScheduledScans()[scanId]->nextRunTime.toString("yyyy-MM-dd hh:mm"))
                             .arg(ui->scanTypeComboBox->currentText())
                             .arg(ui->frequencyComboBox->currentText());
        QMessageBox::information(this, "Scan Scheduled", message);
    } else {
        QMessageBox::critical(this, "Error", "Failed to schedule the scan.");
    }
}

void ScheduleScanPage::checkScheduledScans() {
    for (auto* scan : scheduler->getScheduledScans().values()) {
        if (QDateTime::currentDateTime() >= scan->nextRunTime) {
            QString scanTypeStr;
            switch (scan->type) {
                case ScanType::QUICK:
                    scanTypeStr = "quick";
                    break;
                case ScanType::FULL:
                    scanTypeStr = "system";
                    break;
                case ScanType::CUSTOM:
                    scanTypeStr = "custom";
                    break;
            }
            emit startScan(scanTypeStr, scan->path, scan->interval);
        }
    }
}

void ScheduleScanPage::onScanTypeChanged(int index) {
    selectedScanType = ui->scanTypeComboBox->itemData(index).toString();
}

void ScheduleScanPage::onFrequencyChanged(int index) {
    selectedInterval = static_cast<ScanInterval>(ui->frequencyComboBox->itemData(index).toInt());
}