/********************************************************************************
** Form generated from reading UI file 'historypage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYPAGE_H
#define UI_HISTORYPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoryPage
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *titleLabel;
    QTableWidget *historyTable;

    void setupUi(QWidget *HistoryPage)
    {
        if (HistoryPage->objectName().isEmpty())
            HistoryPage->setObjectName(QString::fromUtf8("HistoryPage"));
        HistoryPage->resize(400, 300);
        HistoryPage->setStyleSheet(QString::fromUtf8("QWidget { background-color: transparent; }\n"
"QLabel { background: none; color: black; }\n"
"QTableWidget {\n"
"    background-color: white;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 5px;\n"
"    selection-background-color: #e0e0e0;\n"
"    selection-color: black;\n"
"}\n"
"\n"
"QPushButton.info-button {\n"
"    background-color: #e0e0e0;\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    min-width: 24px;\n"
"    max-width: 24px;\n"
"    min-height: 24px;\n"
"    max-height: 24px;\n"
"    font-family: Serif;\n"
"    font-weight: bold;\n"
"    color: #404040;\n"
"}\n"
"QPushButton.info-button:hover {\n"
"    background-color: #d0d0d0;\n"
"}\n"
"QPushButton.info-button:pressed {\n"
"    background-color: #c0c0c0;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 5px;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #e0e0e0;\n"
"    color: black;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #f0f0f0;\n"
"    color: black;\n"
"    padding: 5px;\n"
"    bord"
                        "er: 1px solid #d0d0d0;\n"
"    font-family: Serif;\n"
"    font-weight: bold;\n"
"}\n"
"QMessageBox {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"QMessageBox QLabel {\n"
"    color: black;\n"
"    background-color: transparent;\n"
"}\n"
"QMessageBox QPushButton {\n"
"    background-color: #e0e0e0;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 3px;\n"
"    padding: 5px 15px;\n"
"    min-width: 60px;\n"
"}\n"
"QMessageBox QPushButton:hover {\n"
"    background-color: #d0d0d0;\n"
"}"));
        verticalLayout = new QVBoxLayout(HistoryPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        backButton = new QPushButton(HistoryPage);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Serif"));
        backButton->setFont(font);
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    text-align: left;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    background-color: #e0e0e0;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #d0d0d0;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #c0c0c0;\n"
"}"));

        verticalLayout->addWidget(backButton);

        titleLabel = new QLabel(HistoryPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Serif"));
        font1.setPointSize(14);
        font1.setBold(true);
        titleLabel->setFont(font1);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        historyTable = new QTableWidget(HistoryPage);
        historyTable->setObjectName(QString::fromUtf8("historyTable"));
        historyTable->setFont(font);
        historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        historyTable->setAlternatingRowColors(true);
        historyTable->setSelectionMode(QAbstractItemView::SingleSelection);
        historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        historyTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(historyTable);


        retranslateUi(HistoryPage);

        QMetaObject::connectSlotsByName(HistoryPage);
    } // setupUi

    void retranslateUi(QWidget *HistoryPage)
    {
        HistoryPage->setWindowTitle(QCoreApplication::translate("HistoryPage", "Scan History", nullptr));
        backButton->setText(QCoreApplication::translate("HistoryPage", "\342\206\220 Back", nullptr));
        titleLabel->setText(QCoreApplication::translate("HistoryPage", "Scan History", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryPage: public Ui_HistoryPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYPAGE_H
