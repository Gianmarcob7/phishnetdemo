// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scantypepage.h"
#include "schedulescanpage.h"
#include "historypage.h"
#include "quarantinepage.h"
#include "lastscanpage.h"
#include "settingspage.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , schedulePage(nullptr)
   , historyPage(nullptr)
   , scanPage(nullptr)
   , quarantinePage(nullptr)
   , lastScanPage(nullptr)
   , settingsPage(nullptr)
{
   try {
       ui->setupUi(this);
       setupMainWindow();
   }
   catch (const std::exception& e) {
       qDebug() << "Exception in MainWindow constructor:" << e.what();
   }
}



MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::setupMainWindow()
{
    try {
        // Verify buttons exist before connecting
        if (!ui->history_button || !ui->scan_button || !ui->schedule_button ||
            !ui->quar_button || !ui->lastscan_button || !ui->settings_button || !ui->close_button) {
            qDebug() << "One or more buttons are missing in mainwindow UI";
            return;
        }

        connect(ui->history_button, &QPushButton::clicked, this, &MainWindow::openHistoryPage);
        connect(ui->scan_button, &QPushButton::clicked, this, &MainWindow::openScanPage);
        connect(ui->schedule_button, &QPushButton::clicked, this, &MainWindow::openSchedulePage);
        connect(ui->quar_button, &QPushButton::clicked, this, &MainWindow::openQuarantinePage);
        connect(ui->lastscan_button, &QPushButton::clicked, this, &MainWindow::openLastScanPage);
        connect(ui->settings_button, &QPushButton::clicked, this, &MainWindow::openSettingsPage);
        connect(ui->close_button, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);  // Add this line

        updateIconSizes();
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in setupMainWindow:" << e.what();
    }
}

// Add this function implementation
void MainWindow::onCloseButtonClicked()
{
    QApplication::quit();
}

void MainWindow::updateIconSizes()
{
    try {
        int iconSize = qMin(width(), height()) / 8;  // Keep original size for main icons
        int settingsIconSize = iconSize / 3;  // Make settings icon much smaller, changed from * 3/4 to / 3

        if (ui->lastscan_button) ui->lastscan_button->setIconSize(QSize(iconSize, iconSize));
        if (ui->quar_button) ui->quar_button->setIconSize(QSize(iconSize, iconSize));
        if (ui->scan_button) ui->scan_button->setIconSize(QSize(iconSize, iconSize));
        if (ui->history_button) ui->history_button->setIconSize(QSize(iconSize, iconSize));
        if (ui->schedule_button) ui->schedule_button->setIconSize(QSize(iconSize, iconSize));
        if (ui->settings_button) ui->settings_button->setIconSize(QSize(settingsIconSize, settingsIconSize));
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in updateIconSizes:" << e.what();
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   updateIconSizes();
}

void MainWindow::openScanPage()
{
   try {
       scanPage = new ScanTypePage(this);
       connect(scanPage, &ScanTypePage::backButtonClicked, this, &MainWindow::handleBackButton);
       setCentralWidget(scanPage);
   }
   catch (const std::exception& e) {
       qDebug() << "Exception in openScanPage:" << e.what();
   }
}

void MainWindow::openSchedulePage()
{
    try {
        // Delete existing page if it exists
        if (schedulePage) {
            schedulePage->disconnect();
            delete schedulePage;
            schedulePage = nullptr;
        }

               // Create new page
        schedulePage = new ScheduleScanPage(this);
        if (!schedulePage) {
            qDebug() << "Failed to create schedule page!";
            return;
        }

               // Connect signals
        connect(schedulePage, &ScheduleScanPage::backButtonClicked,
                this, &MainWindow::handleBackButton);

        setCentralWidget(schedulePage);
        schedulePage->show();
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in openSchedulePage:" << e.what();
    }
}

void MainWindow::openHistoryPage()
{
   try {
       historyPage = new HistoryPage(this);
       connect(historyPage, &HistoryPage::backButtonClicked, this, &MainWindow::handleBackButton);
       setCentralWidget(historyPage);
   }
   catch (const std::exception& e) {
       qDebug() << "Exception in openHistoryPage:" << e.what();
   }
}

void MainWindow::openQuarantinePage()
{
   try {
       quarantinePage = new QuarantinePage(this);
       connect(quarantinePage, &QuarantinePage::backButtonClicked, this, &MainWindow::handleBackButton);
       setCentralWidget(quarantinePage);
   }
   catch (const std::exception& e) {
       qDebug() << "Exception in openQuarantinePage:" << e.what();
   }
}

void MainWindow::openLastScanPage()
{
   try {
       lastScanPage = new LastScanPage(this);
       connect(lastScanPage, &LastScanPage::backButtonClicked, this, &MainWindow::handleBackButton);
       setCentralWidget(lastScanPage);
   }
   catch (const std::exception& e) {
       qDebug() << "Exception in openLastScanPage:" << e.what();
   }
}

void MainWindow::openSettingsPage()
{
    try {
        qDebug() << "Starting to create settings page...";

               // Clean up existing settings page if it exists
        if (settingsPage) {
            delete settingsPage;
            settingsPage = nullptr;
        }

        settingsPage = new SettingsPage(this);
        if (!settingsPage) {
            qDebug() << "Failed to create settings page!";
            return;
        }

        qDebug() << "Connecting back button signal...";
        bool connected = connect(settingsPage, &SettingsPage::backButtonClicked,
                                 this, &MainWindow::handleBackButton);
        if (!connected) {
            qDebug() << "Failed to connect back button signal!";
        }

               // Add the dark mode connection here
        connect(settingsPage, &SettingsPage::darkModeChanged,
                this, &MainWindow::handleDarkModeChange);

        qDebug() << "Setting central widget...";
        setCentralWidget(settingsPage);
        qDebug() << "Settings page opened successfully";
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in openSettingsPage:" << e.what();
    }
    catch (...) {
        qDebug() << "Unknown exception in openSettingsPage";
    }
}

// Add the handler function implementation at the end of mainwindow.cpp
void MainWindow::handleDarkModeChange(bool isDark)
{
    SettingsPage::applyDarkMode(this, isDark);
}

void MainWindow::handleBackButton()
{
   try {
       qDebug() << "Handling back button click...";

       if (QWidget* oldWidget = centralWidget()) {
           oldWidget->disconnect();
           oldWidget->deleteLater();
       }
       setCentralWidget(nullptr);

       schedulePage = nullptr;
       historyPage = nullptr;
       scanPage = nullptr;
       quarantinePage = nullptr;
       lastScanPage = nullptr;
       settingsPage = nullptr;

       qDebug() << "Setting up main UI...";
       ui->setupUi(this);
       setupMainWindow();

       qDebug() << "Back button handled successfully";
   }
   catch (const std::exception& e) {
       qDebug() << "Exception in handleBackButton:" << e.what();
   }
}
