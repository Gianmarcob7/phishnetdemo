#ifndef LASTSCANPAGE_H
#define LASTSCANPAGE_H

#include <QWidget>
#include <QDateTime>
#include "Database.h"

namespace Ui {
class LastScanPage;
}

class LastScanPage : public QWidget {
    Q_OBJECT

  public:
    explicit LastScanPage(QWidget *parent = nullptr);
    ~LastScanPage();

  private slots:
    void onBackButtonClicked();
    void onRescanButtonClicked();
    void onViewDetailsClicked();

  signals:
    void backButtonClicked();
    void startScan(const QString& scanType);

  private:
    Ui::LastScanPage *ui;
    Database db;
    ScanSession lastScanSession;
    void loadLastScanInfo();
};

#endif