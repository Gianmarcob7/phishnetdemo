#ifndef QUARANTINEPAGE_H
#define QUARANTINEPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>

namespace Ui {
class QuarantinePage;
}

class QuarantinePage : public QWidget
{
    Q_OBJECT

public:
    explicit QuarantinePage(QWidget *parent = nullptr);
    ~QuarantinePage();

private slots:
    void onBackButtonClicked();
    void onDeleteButtonClicked();
    void onKeepButtonClicked();
    void onItemSelectionChanged();

signals:
    void backButtonClicked();

private:
    Ui::QuarantinePage *ui;
    void loadQuarantinedFiles();
    void updateButtons();
    void setMessageBoxStyle(QMessageBox* msgBox);
};

#endif // QUARANTINEPAGE_H