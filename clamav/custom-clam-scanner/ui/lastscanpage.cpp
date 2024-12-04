// lastscanpage.cpp
#include "lastscanpage.h"
#include "ui_lastscanpage.h"
#include <QMessageBox>

LastScanPage::LastScanPage(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::LastScanPage)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &LastScanPage::onBackButtonClicked);
    connect(ui->rescanButton, &QPushButton::clicked, this, &LastScanPage::onRescanButtonClicked);
    connect(ui->viewDetailsButton, &QPushButton::clicked, this, &LastScanPage::onViewDetailsClicked);

    loadLastScanInfo();
}

LastScanPage::~LastScanPage()
{
    delete ui;
}

void LastScanPage::onBackButtonClicked()
{
    emit backButtonClicked();
}

void LastScanPage::loadLastScanInfo()
{
    // TODO: Load actual last scan data
    ui->dateTimeLabel->setText("Last Scan: 2024-03-20 15:30");
    ui->scanTypeLabel->setText("Scan Type: Quick Scan");
    ui->durationLabel->setText("Duration: 5 minutes");
    ui->filesScannedLabel->setText("Files Scanned: 1,234");
    ui->threatsFoundLabel->setText("Threats Found: 2");
    ui->statusLabel->setText("Status: Completed");
}

void LastScanPage::onRescanButtonClicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Rescan");
    msgBox.setText("Starting new scan with previous settings...");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #f0f0f0; }"
        "QPushButton { background-color: #666666; color: white; border: none; padding: 6px 12px; border-radius: 4px; }"
        );
    msgBox.exec();
}

void LastScanPage::onViewDetailsClicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Scan Details");
    msgBox.setText(
        "Detailed Scan Information:\n\n"
        "Start Time: 2024-03-20 15:30\n"
        "End Time: 2024-03-20 15:35\n"
        "Scan Type: Quick Scan\n"
        "Areas Scanned: System Memory, Startup Items, Registry\n"
        "Total Files: 1,234\n"
        "Threats Found: 2\n"
        "Threats Removed: 2\n"
        "Status: Completed Successfully"
        );
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #f0f0f0; }"
        "QPushButton { background-color: #666666; color: white; border: none; padding: 6px 12px; border-radius: 4px; }"
        );
    msgBox.exec();
}
