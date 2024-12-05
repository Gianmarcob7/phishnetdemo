#include "historypage.h"
#include "ui_historypage.h"
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QTableWidgetItem>

HistoryPage::HistoryPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryPage),
    database(new Database())
{
    ui->setupUi(this);

    // Set up the table
    setupTable();

    // Connect signals
    connect(ui->backButton, &QPushButton::clicked,
            this, &HistoryPage::onBackButtonClicked);

    // Load history data
    refreshHistory();
}

HistoryPage::~HistoryPage()
{
    delete database;
    delete ui;
}

void HistoryPage::setupTable()
{
    ui->historyTable->setColumnCount(6);
    QStringList headers;
    headers << "Session ID" << "Date/Time" << "Scan Type" << "Files Scanned" << "Status" << "Details";
    ui->historyTable->setHorizontalHeaderLabels(headers);

    // Set column widths
    ui->historyTable->setColumnWidth(0, 150); // Session ID
    ui->historyTable->setColumnWidth(1, 150); // Date/Time
    ui->historyTable->setColumnWidth(2, 100); // Scan Type
    ui->historyTable->setColumnWidth(3, 100); // Files Scanned
    ui->historyTable->setColumnWidth(4, 100); // Status
    ui->historyTable->setColumnWidth(5, 80);  // Details button
}

void HistoryPage::refreshHistory()
{
    ui->historyTable->setRowCount(0); // Clear existing items

    // Get recent sessions from database
    std::vector<ScanSession> sessions = database->getRecentSessions();

    for(const auto& session : sessions) {
        int row = ui->historyTable->rowCount();
        ui->historyTable->insertRow(row);

        // Session ID
        ui->historyTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(session.session_id)));
        
        // Date/Time (combine start time for display)
        ui->historyTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(session.start_time)));
        
        // Scan Type
        ui->historyTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(session.scan_type)));
        
        // Files Scanned
        ui->historyTable->setItem(row, 3, new QTableWidgetItem(QString::number(session.files_scanned)));

        // Status with color coding
        QTableWidgetItem *statusItem = new QTableWidgetItem(
            session.threats_found > 0 ? QString("Threats: %1").arg(session.threats_found) : "Clean"
        );
        statusItem->setForeground(session.threats_found > 0 ? Qt::red : Qt::darkGreen);
        statusItem->setFont(QFont("Serif", -1, session.threats_found > 0 ? QFont::Bold : QFont::Normal));
        ui->historyTable->setItem(row, 4, statusItem);

        // Create info button
        QPushButton* infoButton = new QPushButton("i", ui->historyTable);
        infoButton->setFixedSize(24, 24);
        infoButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #e0e0e0;"
            "   border: none;"
            "   border-radius: 12px;"
            "   font-family: Serif;"
            "   font-weight: bold;"
            "   color: #404040;"
            "}"
            "QPushButton:hover {"
            "   background-color: #d0d0d0;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #c0c0c0;"
            "}"
        );
        infoButton->setCursor(Qt::PointingHandCursor);

        // Connect button to show session details
        connect(infoButton, &QPushButton::clicked, this, [this, session]() {
            showSessionDetails(session);
        });

        ui->historyTable->setCellWidget(row, 5, infoButton);
    }
}

void HistoryPage::showSessionDetails(const ScanSession& session)
{
    // Get detailed results for this session
    std::vector<ScanRecord> records = database->getSessionResults(session.session_id);
    
    QString details = QString("Session Details:\n\n"
                            "Session ID: %1\n"
                            "Scan Type: %2\n"
                            "Start Time: %3\n"
                            "End Time: %4\n"
                            "Files Scanned: %5\n"
                            "Threats Found: %6\n\n")
                         .arg(QString::fromStdString(session.session_id))
                         .arg(QString::fromStdString(session.scan_type))
                         .arg(QString::fromStdString(session.start_time))
                         .arg(QString::fromStdString(session.end_time))
                         .arg(session.files_scanned)
                         .arg(session.threats_found);

    // Add threat details if any were found
    if (session.threats_found > 0) {
        details += "Detected Threats:\n";
        details += "----------------\n";
        for (const auto& record : records) {
            if (record.detected) {
                details += QString("\nFile: %1\n"
                                 "Threat: %2\n"
                                 "Detected: %3\n")
                              .arg(QString::fromStdString(record.file_path))
                              .arg(QString::fromStdString(record.threat_name))
                              .arg(QString::fromStdString(record.scan_date));
            }
        }
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Scan Details");
    msgBox.setText(details);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #f0f0f0; }"
        "QMessageBox QLabel { color: #333333; font-family: Serif; font-size: 12px; padding: 10px; }"
        "QPushButton { background-color: #666666; color: white; border: none; padding: 6px 12px; "
        "              border-radius: 4px; font-family: Serif; font-weight: bold; min-width: 80px; }"
        "QPushButton:hover { background-color: #555555; }"
    );
    msgBox.exec();
}

void HistoryPage::onBackButtonClicked()
{
    emit backButtonClicked();
}