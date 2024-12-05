// customfiledialog.h
#ifndef CUSTOMFILEDIALOG_H
#define CUSTOMFILEDIALOG_H

#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

class CustomFileDialog : public QFileDialog {
    Q_OBJECT

public:
    explicit CustomFileDialog(QWidget* parent = nullptr);

public slots:
    void selectCurrentDirectory();
};

#endif // CUSTOMFILEDIALOG_H