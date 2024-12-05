#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "scantypepage.h"
#include "schedulescanpage.h"
#include "historypage.h"
#include "quarantinepage.h"
#include "lastscanpage.h"
#include "settingspage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupMainWindow();

public slots:
    void handleDarkModeChange(bool isDark);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void openScanPage();
    void openSchedulePage();
    void openHistoryPage();
    void openQuarantinePage();
    void openLastScanPage();
    void openSettingsPage();
    void handleBackButton();
    void updateIconSizes();
    void onCloseButtonClicked();

private:
    Ui::MainWindow *ui;
    ScanTypePage *scanPage;
    ScheduleScanPage *schedulePage;
    HistoryPage *historyPage;
    QuarantinePage *quarantinePage;
    LastScanPage *lastScanPage;
    SettingsPage *settingsPage;
};

#endif // MAINWINDOW_H