#include "scantypepage.h"
#include "ui_scantypepage.h"
#include "customfiledialog.h"
#include <QMessageBox>
#include <QButtonGroup>
#include <QFileDialog>
#include <QProgressDialog>
#include <QDateTime>
#include <QFileInfo>
#include <QDialogButtonBox>
#include <QVBoxLayout>

ScanTypePage::ScanTypePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScanTypePage)
    , scanThread(nullptr)
    , worker(nullptr)
    , scheduleTimer(nullptr)
{
    ui->setupUi(this);

    // Connect signals
    connect(ui->backButton, &QPushButton::clicked, this, &ScanTypePage::onBackButtonClicked);
    connect(ui->quickScanButton, &QPushButton::clicked, this, &ScanTypePage::startQuickScan);
    connect(ui->systemScanButton, &QPushButton::clicked, this, &ScanTypePage::startSystemScan);
    connect(ui->customScanButton, &QPushButton::clicked, this, &ScanTypePage::onCustomScanButtonClicked);
    connect(ui->browseButton, &QPushButton::clicked, this, &ScanTypePage::onBrowseButtonClicked);

    ui->stackedWidget->setCurrentIndex(0);
    ui->startCustomScanButton->setEnabled(false);
    
    setupScanWorker();
    setupScheduler();
}

ScanTypePage::~ScanTypePage()
{
    if (scanThread) {
        scanThread->quit();
        scanThread->wait();
        delete scanThread;
    }
    if (scheduleTimer) {
        scheduleTimer->stop();
        delete scheduleTimer;
    }
    delete ui;
}

void ScanTypePage::setupScanWorker()
{
    scanThread = new QThread(this);
    worker = new ScanWorker();
    worker->moveToThread(scanThread);

    connect(this, &ScanTypePage::startScan, worker, &ScanWorker::doScan);
    connect(worker, &ScanWorker::scanComplete, this, &ScanTypePage::handleScanComplete);
    connect(worker, &ScanWorker::scanProgress, this, &ScanTypePage::updateScanProgress);
    connect(scanThread, &QThread::finished, worker, &QObject::deleteLater);

    scanThread->start();
}

void ScanTypePage::setupScheduler()
{
    scheduleTimer = new QTimer(this);
    connect(scheduleTimer, &QTimer::timeout, this, &ScanTypePage::checkScheduledScans);
    scheduleTimer->start(60000); // Check every minute
}

void ScanTypePage::setMessageBoxStyle(QMessageBox* msgBox)
{
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: #f0f0f0;"
        "    color: #333333;"
        "}"
        "QMessageBox QLabel {"
        "    color: #333333;"
        "    font-family: Serif;"
        "    font-size: 12px;"
        "    padding: 10px;"
        "}"
        "QPushButton {"
        "    background-color: #666666;"
        "    color: white;"
        "    border: none;"
        "    padding: 6px 12px;"
        "    border-radius: 4px;"
        "    font-family: Serif;"
        "    font-weight: bold;"
        "    min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #555555;"
        "}"
    );
}

void ScanTypePage::onBackButtonClicked()
{
    emit backButtonClicked();
}

void ScanTypePage::onBrowseButtonClicked()
{
    CustomFileDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            selectedDirectory = files.first();
            ui->startCustomScanButton->setEnabled(true);
            
            QMessageBox* msgBox = new QMessageBox(this);
            msgBox->setWindowTitle("Selected Path");
            QString pathType = QFileInfo(selectedDirectory).isDir() ? "directory" : "file";
            msgBox->setText("Selected " + pathType + " for scanning: \n" + selectedDirectory);
            setMessageBoxStyle(msgBox);
            msgBox->exec();
            delete msgBox;
        }
    }
}

void ScanTypePage::onCustomScanButtonClicked()
{
    CustomFileDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            selectedDirectory = files.first();
            ui->startCustomScanButton->setEnabled(true);
            startCustomScan();
        }
    }
}

void ScanTypePage::startQuickScan()
{
    QProgressDialog* progressDialog = new QProgressDialog("Starting Quick Scan...", "Cancel", 0, 0, this);
    progressDialog->setWindowTitle("Quick Scan");
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setAutoClose(false);
    progressDialog->setAutoReset(false);
    progressDialog->setMinimumDuration(0);
    progressDialog->show();

    worker->setScanType("quick");
    
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Quick Scan");
    msgBox->setText("Starting Quick Scan...\n\nScanning user directories for potential threats.");
    setMessageBoxStyle(msgBox);
    msgBox->exec();
    delete msgBox;

    emit startScan();
}

void ScanTypePage::startSystemScan()
{
    QProgressDialog* progressDialog = new QProgressDialog("Starting System Scan...", "Cancel", 0, 0, this);
    progressDialog->setWindowTitle("System Scan");
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setAutoClose(false);
    progressDialog->setAutoReset(false);
    progressDialog->show();

    worker->setScanType("system");
    
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("System Scan");
    msgBox->setText("Starting System Scan...\n\nThis may take some time.");
    setMessageBoxStyle(msgBox);
    msgBox->exec();
    delete msgBox;

    emit startScan();
}

void ScanTypePage::startCustomScan()
{
    QProgressDialog* progressDialog = new QProgressDialog("Starting Custom Scan...", "Cancel", 0, 0, this);
    progressDialog->setWindowTitle("Custom Scan");
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setAutoClose(false);
    progressDialog->setAutoReset(false);
    progressDialog->show();

    worker->setScanType("custom");
    worker->setScanPath(selectedDirectory);

    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Custom Scan");
    QString pathType = QFileInfo(selectedDirectory).isDir() ? "directory" : "file";
    msgBox->setText("Starting Custom Scan of " + pathType + ":\n" + selectedDirectory);
    setMessageBoxStyle(msgBox);
    msgBox->exec();
    delete msgBox;

    emit startScan();
}

void ScanTypePage::handleScanComplete(int filesScanned, int threatsFound)
{
    QList<QProgressDialog*> progressDialogs = findChildren<QProgressDialog*>();
    for (QProgressDialog* dialog : progressDialogs) {
        dialog->close();
        dialog->deleteLater();
    }

    QString message = QString("Scan Complete!\n\n"
                            "Files Scanned: %1\n"
                            "Threats Found: %2\n\n")
                         .arg(filesScanned)
                         .arg(threatsFound);
    
    if (threatsFound > 0) {
        message += QString("Threats have been moved to quarantine at:\n%1")
                      .arg("/home/gianmarco/clamav/custom-clam-scanner/build/Quarantine");
    } else {
        message += "No threats were detected.";
    }

    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Scan Results");
    msgBox->setText(message);
    setMessageBoxStyle(msgBox);
    msgBox->exec();
    delete msgBox;
}

void ScanTypePage::updateScanProgress(int filesScanned)
{
    QList<QProgressDialog*> progressDialogs = findChildren<QProgressDialog*>();
    for (QProgressDialog* dialog : progressDialogs) {
        dialog->setLabelText(QString("Scanning...\nFiles processed: %1\nPlease wait...")
                               .arg(filesScanned));
        dialog->setMinimum(0);
        dialog->setMaximum(0);
    }
}

void ScanTypePage::checkScheduledScans()
{
    if (!scheduledScanTime.isValid()) return;
    
    if (QDateTime::currentDateTime() >= scheduledScanTime) {
        // Time to run the scheduled scan
        if (scheduledScanType == "quick") {
            startQuickScan();
        } else if (scheduledScanType == "system") {
            startSystemScan();
        } else if (scheduledScanType == "custom") {
            startCustomScan();
        }
        
        // Clear the scheduled time after running
        scheduledScanTime = QDateTime();
        scheduledScanType.clear();
    }
}

void ScanTypePage::onScanTypeChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    
    // Store the selected scan type
    switch(index) {
        case 0:
            scheduledScanType = "quick";
            break;
        case 1:
            scheduledScanType = "system";
            break;
        case 2:
            scheduledScanType = "custom";
            break;
    }
}