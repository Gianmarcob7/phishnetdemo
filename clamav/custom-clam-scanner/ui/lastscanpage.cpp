#include "lastscanpage.h"
#include "ui_lastscanpage.h"
#include <QMessageBox>

LastScanPage::LastScanPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LastScanPage)
    , db()
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
    // Get the most recent scan session from the database
    std::vector<ScanSession> sessions = db.getRecentSessions(1);
    if (!sessions.empty()) {
        lastScanSession = sessions[0];

        // Update the UI with the last scan information
        ui->dateTimeLabel->setText("Last Scan: " + QString::fromStdString(lastScanSession.start_time));
        ui->scanTypeLabel->setText("Scan Type: " + QString::fromStdString(lastScanSession.scan_type));
        ui->durationLabel->setText("Duration: " + QString::number(db.getDurationInMinutes(lastScanSession)) + " minutes");
        ui->filesScannedLabel->setText("Files Scanned: " + QString::number(lastScanSession.files_scanned));
        ui->threatsFoundLabel->setText("Threats Found: " + QString::number(lastScanSession.threats_found));
        ui->statusLabel->setText("Status: " + (lastScanSession.end_time.empty() ? QString("In Progress") : QString("Completed")));
    } else {
        // No scan history found
        ui->dateTimeLabel->setText("Last Scan: N/A");
        ui->scanTypeLabel->setText("Scan Type: N/A");
        ui->durationLabel->setText("Duration: N/A");
        ui->filesScannedLabel->setText("Files Scanned: N/A");
        ui->threatsFoundLabel->setText("Threats Found: N/A");
        ui->statusLabel->setText("Status: N/A");
    }
}

void LastScanPage::onRescanButtonClicked()
{
    // Start a new scan with the same settings as the last scan
    emit startScan(QString::fromStdString(lastScanSession.scan_type));
}

void LastScanPage::onViewDetailsClicked()
{
    // Display the detailed scan report for the last scan
    std::string scanSummary = db.getScanSummary(lastScanSession.session_id);
    std::vector<ScanRecord> scanResults = db.getSessionResults(lastScanSession.session_id);

    QString detailsText = "Detailed Scan Information:\n\n" + QString::fromStdString(scanSummary) + "\n\nDetected Threats:\n";
    for (const auto& record : scanResults) {
        if (record.detected) {
            detailsText += "File: " + QString::fromStdString(record.file_path) + "\n";
            detailsText += "Threat: " + QString::fromStdString(record.threat_name) + "\n";
            detailsText += "Detection Time: " + QString::fromStdString(record.scan_date) + "\n\n";
        }
    }

    if (scanResults.empty()) {
        detailsText += "No threats were detected during this scan.";
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Scan Details");
    msgBox.setText(detailsText);
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #f0f0f0; }"
        "QPushButton { background-color: #666666; color: white; border: none; padding: 6px 12px; border-radius: 4px; }"
    );
    msgBox.exec();
}