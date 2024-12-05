// historypage.h
#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QObject>
#include "Database.h"

namespace Ui {
class HistoryPage;
}

class HistoryPage : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryPage(QWidget *parent = nullptr);
    ~HistoryPage();

private slots:
    void onBackButtonClicked();
    void refreshHistory();

signals:
    void backButtonClicked();

private:
    Ui::HistoryPage *ui;
    Database* database;
    void setupTable();
    void showSessionDetails(const ScanSession& session);
};

#endif // HISTORYPAGE_H