/********************************************************************************
** Form generated from reading UI file 'schedulescanpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULESCANPAGE_H
#define UI_SCHEDULESCANPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleScanPage
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *titleLabel;
    QLabel *frequencyLabel;
    QComboBox *frequencyComboBox;
    QLabel *timeLabel;
    QHBoxLayout *timeLayout;
    QComboBox *hourComboBox;
    QLabel *colonLabel;
    QComboBox *minuteComboBox;
    QSpacerItem *verticalSpacer;
    QPushButton *scheduleButton;

    void setupUi(QWidget *ScheduleScanPage)
    {
        if (ScheduleScanPage->objectName().isEmpty())
            ScheduleScanPage->setObjectName(QString::fromUtf8("ScheduleScanPage"));
        ScheduleScanPage->resize(400, 300);
        ScheduleScanPage->setStyleSheet(QString::fromUtf8("QWidget { background-color: transparent; }\n"
"QLabel { background: none; color: black; }\n"
"QComboBox {\n"
"    background-color: white;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    selection-background-color: #e0e0e0;\n"
"    selection-color: black;\n"
"}\n"
"QComboBox:hover {\n"
"    border-color: #b0b0b0;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"}\n"
"QComboBox::down-arrow {\n"
"    image: url(down_arrow.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: white;\n"
"    border: 1px solid #d0d0d0;\n"
"    selection-background-color: #e0e0e0;\n"
"    selection-color: black;\n"
"}\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 25px;\n"
"    padding: 5px;\n"
"    background-color: white;\n"
"    color: black;\n"
"}\n"
"QComboBox QAbstractItemView::item:selected {\n"
"    background-color: #d0d0d0;\n"
"    color: black;\n"
"}\n"
"QComboBox QAbstractItemView::item:hover {"
                        "\n"
"    background-color: #e0e0e0;\n"
"    color: black;\n"
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
"}\n"
"QDialog {\n"
"    background-color: #f0f0f0;\n"
"}"));
        verticalLayout = new QVBoxLayout(ScheduleScanPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        backButton = new QPushButton(ScheduleScanPage);
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
"QPushButton:checked {\n"
"    background-color: #c0c0c0;\n"
"    color: #cc0000;\n"
"    font-weight: bold;\n"
"}"));

        verticalLayout->addWidget(backButton);

        titleLabel = new QLabel(ScheduleScanPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Serif"));
        font1.setPointSize(14);
        font1.setBold(true);
        titleLabel->setFont(font1);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        frequencyLabel = new QLabel(ScheduleScanPage);
        frequencyLabel->setObjectName(QString::fromUtf8("frequencyLabel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Serif"));
        font2.setBold(true);
        frequencyLabel->setFont(font2);

        verticalLayout->addWidget(frequencyLabel);

        frequencyComboBox = new QComboBox(ScheduleScanPage);
        frequencyComboBox->setObjectName(QString::fromUtf8("frequencyComboBox"));
        frequencyComboBox->setFont(font);
        frequencyComboBox->setMinimumWidth(200);

        verticalLayout->addWidget(frequencyComboBox);

        timeLabel = new QLabel(ScheduleScanPage);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setFont(font2);

        verticalLayout->addWidget(timeLabel);

        timeLayout = new QHBoxLayout();
        timeLayout->setSpacing(5);
        timeLayout->setObjectName(QString::fromUtf8("timeLayout"));
        hourComboBox = new QComboBox(ScheduleScanPage);
        hourComboBox->setObjectName(QString::fromUtf8("hourComboBox"));
        hourComboBox->setFont(font);
        hourComboBox->setMinimumWidth(80);

        timeLayout->addWidget(hourComboBox);

        colonLabel = new QLabel(ScheduleScanPage);
        colonLabel->setObjectName(QString::fromUtf8("colonLabel"));
        colonLabel->setMaximumWidth(10);
        colonLabel->setAlignment(Qt::AlignCenter);

        timeLayout->addWidget(colonLabel);

        minuteComboBox = new QComboBox(ScheduleScanPage);
        minuteComboBox->setObjectName(QString::fromUtf8("minuteComboBox"));
        minuteComboBox->setFont(font);
        minuteComboBox->setMinimumWidth(80);

        timeLayout->addWidget(minuteComboBox);


        verticalLayout->addLayout(timeLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scheduleButton = new QPushButton(ScheduleScanPage);
        scheduleButton->setObjectName(QString::fromUtf8("scheduleButton"));
        scheduleButton->setFont(font2);
        scheduleButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #cc0000;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #b30000;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #990000;\n"
"}"));

        verticalLayout->addWidget(scheduleButton);


        retranslateUi(ScheduleScanPage);

        QMetaObject::connectSlotsByName(ScheduleScanPage);
    } // setupUi

    void retranslateUi(QWidget *ScheduleScanPage)
    {
        ScheduleScanPage->setWindowTitle(QCoreApplication::translate("ScheduleScanPage", "Schedule Scan", nullptr));
        backButton->setText(QCoreApplication::translate("ScheduleScanPage", "\342\206\220 Back", nullptr));
        titleLabel->setText(QCoreApplication::translate("ScheduleScanPage", "Schedule Scan", nullptr));
        frequencyLabel->setText(QCoreApplication::translate("ScheduleScanPage", "Scan Frequency:", nullptr));
        timeLabel->setText(QCoreApplication::translate("ScheduleScanPage", "Scan Time:", nullptr));
        colonLabel->setText(QCoreApplication::translate("ScheduleScanPage", ":", nullptr));
        scheduleButton->setText(QCoreApplication::translate("ScheduleScanPage", "Schedule Scan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScheduleScanPage: public Ui_ScheduleScanPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULESCANPAGE_H
