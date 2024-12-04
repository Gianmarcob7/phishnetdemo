// lastscanpage.h
#ifndef LASTSCANPAGE_H
#define LASTSCANPAGE_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class LastScanPage;
}

class LastScanPage : public QWidget
{
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

  private:
    Ui::LastScanPage *ui;
    void loadLastScanInfo();
};

#endif
