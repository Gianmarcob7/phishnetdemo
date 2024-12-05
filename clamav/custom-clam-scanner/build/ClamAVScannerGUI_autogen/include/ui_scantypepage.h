/********************************************************************************
** Form generated from reading UI file 'scantypepage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANTYPEPAGE_H
#define UI_SCANTYPEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanTypePage
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *sidePanel;
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *titleLabel;
    QPushButton *quickScanButton;
    QPushButton *systemScanButton;
    QPushButton *customScanButton;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *quickScanPage;
    QVBoxLayout *verticalLayout_2;
    QLabel *quickScanTitle;
    QFrame *quickScanFrame;
    QVBoxLayout *verticalLayout_5;
    QLabel *quickScanLabel;
    QPushButton *startQuickScanButton;
    QWidget *systemScanPage;
    QVBoxLayout *verticalLayout_3;
    QLabel *systemScanTitle;
    QFrame *systemScanFrame;
    QVBoxLayout *verticalLayout_6;
    QLabel *systemScanLabel;
    QPushButton *startSystemScanButton;
    QWidget *customScanPage;
    QVBoxLayout *verticalLayout_4;
    QLabel *customScanTitle;
    QFrame *customScanFrame;
    QVBoxLayout *verticalLayout_7;
    QLabel *customScanLabel;
    QPushButton *browseButton;
    QPushButton *startCustomScanButton;

    void setupUi(QWidget *ScanTypePage)
    {
        if (ScanTypePage->objectName().isEmpty())
            ScanTypePage->setObjectName(QString::fromUtf8("ScanTypePage"));
        ScanTypePage->resize(800, 600);
        horizontalLayout = new QHBoxLayout(ScanTypePage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sidePanel = new QFrame(ScanTypePage);
        sidePanel->setObjectName(QString::fromUtf8("sidePanel"));
        sidePanel->setMaximumWidth(200);
        sidePanel->setStyleSheet(QString::fromUtf8("QFrame#sidePanel {\n"
"    background-color: #f0f0f0;\n"
"    border-right: 1px solid #dcdcdc;\n"
"}\n"
"QPushButton {\n"
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
"}\n"
"QLabel#titleLabel {\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"    background: none;\n"
"}"));
        verticalLayout = new QVBoxLayout(sidePanel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        backButton = new QPushButton(sidePanel);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Serif"));
        backButton->setFont(font);

        verticalLayout->addWidget(backButton);

        titleLabel = new QLabel(sidePanel);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Serif"));
        font1.setBold(true);
        titleLabel->setFont(font1);

        verticalLayout->addWidget(titleLabel);

        quickScanButton = new QPushButton(sidePanel);
        quickScanButton->setObjectName(QString::fromUtf8("quickScanButton"));
        quickScanButton->setFont(font);
        quickScanButton->setCheckable(true);
        quickScanButton->setChecked(true);

        verticalLayout->addWidget(quickScanButton);

        systemScanButton = new QPushButton(sidePanel);
        systemScanButton->setObjectName(QString::fromUtf8("systemScanButton"));
        systemScanButton->setFont(font);
        systemScanButton->setCheckable(true);

        verticalLayout->addWidget(systemScanButton);

        customScanButton = new QPushButton(sidePanel);
        customScanButton->setObjectName(QString::fromUtf8("customScanButton"));
        customScanButton->setFont(font);
        customScanButton->setCheckable(true);

        verticalLayout->addWidget(customScanButton);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(sidePanel);

        stackedWidget = new QStackedWidget(ScanTypePage);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        quickScanPage = new QWidget();
        quickScanPage->setObjectName(QString::fromUtf8("quickScanPage"));
        verticalLayout_2 = new QVBoxLayout(quickScanPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        quickScanTitle = new QLabel(quickScanPage);
        quickScanTitle->setObjectName(QString::fromUtf8("quickScanTitle"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Serif"));
        font2.setPointSize(12);
        font2.setBold(true);
        quickScanTitle->setFont(font2);
        quickScanTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(quickScanTitle);

        quickScanFrame = new QFrame(quickScanPage);
        quickScanFrame->setObjectName(QString::fromUtf8("quickScanFrame"));
        quickScanFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border: 1px solid #dcdcdc;\n"
"    border-radius: 8px;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(quickScanFrame);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        quickScanLabel = new QLabel(quickScanFrame);
        quickScanLabel->setObjectName(QString::fromUtf8("quickScanLabel"));
        quickScanLabel->setFont(font);
        quickScanLabel->setStyleSheet(QString::fromUtf8("border: none;"));
        quickScanLabel->setWordWrap(true);

        verticalLayout_5->addWidget(quickScanLabel);

        startQuickScanButton = new QPushButton(quickScanFrame);
        startQuickScanButton->setObjectName(QString::fromUtf8("startQuickScanButton"));
        startQuickScanButton->setFont(font);
        startQuickScanButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #cc0000;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #b30000;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #990000;\n"
"}"));

        verticalLayout_5->addWidget(startQuickScanButton);


        verticalLayout_2->addWidget(quickScanFrame);

        stackedWidget->addWidget(quickScanPage);
        systemScanPage = new QWidget();
        systemScanPage->setObjectName(QString::fromUtf8("systemScanPage"));
        verticalLayout_3 = new QVBoxLayout(systemScanPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        systemScanTitle = new QLabel(systemScanPage);
        systemScanTitle->setObjectName(QString::fromUtf8("systemScanTitle"));
        systemScanTitle->setFont(font2);
        systemScanTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(systemScanTitle);

        systemScanFrame = new QFrame(systemScanPage);
        systemScanFrame->setObjectName(QString::fromUtf8("systemScanFrame"));
        systemScanFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border: 1px solid #dcdcdc;\n"
"    border-radius: 8px;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(systemScanFrame);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        systemScanLabel = new QLabel(systemScanFrame);
        systemScanLabel->setObjectName(QString::fromUtf8("systemScanLabel"));
        systemScanLabel->setFont(font);
        systemScanLabel->setStyleSheet(QString::fromUtf8("border: none;"));
        systemScanLabel->setWordWrap(true);

        verticalLayout_6->addWidget(systemScanLabel);

        startSystemScanButton = new QPushButton(systemScanFrame);
        startSystemScanButton->setObjectName(QString::fromUtf8("startSystemScanButton"));
        startSystemScanButton->setFont(font);
        startSystemScanButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #cc0000;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #b30000;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #990000;\n"
"}"));

        verticalLayout_6->addWidget(startSystemScanButton);


        verticalLayout_3->addWidget(systemScanFrame);

        stackedWidget->addWidget(systemScanPage);
        customScanPage = new QWidget();
        customScanPage->setObjectName(QString::fromUtf8("customScanPage"));
        verticalLayout_4 = new QVBoxLayout(customScanPage);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        customScanTitle = new QLabel(customScanPage);
        customScanTitle->setObjectName(QString::fromUtf8("customScanTitle"));
        customScanTitle->setFont(font2);
        customScanTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(customScanTitle);

        customScanFrame = new QFrame(customScanPage);
        customScanFrame->setObjectName(QString::fromUtf8("customScanFrame"));
        customScanFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border: 1px solid #dcdcdc;\n"
"    border-radius: 8px;\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(customScanFrame);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        customScanLabel = new QLabel(customScanFrame);
        customScanLabel->setObjectName(QString::fromUtf8("customScanLabel"));
        customScanLabel->setFont(font);
        customScanLabel->setStyleSheet(QString::fromUtf8("border: none;"));
        customScanLabel->setWordWrap(true);

        verticalLayout_7->addWidget(customScanLabel);

        browseButton = new QPushButton(customScanFrame);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setFont(font);
        browseButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #666666;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #555555;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #444444;\n"
"}"));

        verticalLayout_7->addWidget(browseButton);

        startCustomScanButton = new QPushButton(customScanFrame);
        startCustomScanButton->setObjectName(QString::fromUtf8("startCustomScanButton"));
        startCustomScanButton->setFont(font);
        startCustomScanButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #cc0000;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #b30000;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #990000;\n"
"}"));

        verticalLayout_7->addWidget(startCustomScanButton);


        verticalLayout_4->addWidget(customScanFrame);

        stackedWidget->addWidget(customScanPage);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ScanTypePage);

        QMetaObject::connectSlotsByName(ScanTypePage);
    } // setupUi

    void retranslateUi(QWidget *ScanTypePage)
    {
        backButton->setText(QCoreApplication::translate("ScanTypePage", "\342\206\220 Back", nullptr));
        titleLabel->setText(QCoreApplication::translate("ScanTypePage", "Choose Scan Type", nullptr));
        quickScanButton->setText(QCoreApplication::translate("ScanTypePage", "Quick Scan", nullptr));
        systemScanButton->setText(QCoreApplication::translate("ScanTypePage", "System Scan", nullptr));
        customScanButton->setText(QCoreApplication::translate("ScanTypePage", "Custom Scan", nullptr));
        quickScanTitle->setText(QCoreApplication::translate("ScanTypePage", "Quick Scan Description", nullptr));
        quickScanLabel->setText(QCoreApplication::translate("ScanTypePage", "Quick Scan checks the most commonly infected areas of your system, including:\n"
"\n"
"- System Memory\n"
"- Startup Items\n"
"- Critical System Files\n"
"- Windows Startup Folders\n"
"- Profile Directories\n"
"- Registration Keys\n"
"\n"
"This scan typically takes 5-10 minutes to complete.", nullptr));
        startQuickScanButton->setText(QCoreApplication::translate("ScanTypePage", "Start Quick Scan", nullptr));
        systemScanTitle->setText(QCoreApplication::translate("ScanTypePage", "System Scan Description", nullptr));
        systemScanLabel->setText(QCoreApplication::translate("ScanTypePage", "System Scan performs a thorough check of your entire system, including:\n"
"\n"
"- All Files and Directories\n"
"- Running Processes\n"
"- System Registry\n"
"- Hidden Files\n"
"- Network Connections\n"
"- System Memory\n"
"- Bootable Sectors\n"
"\n"
"This scan may take 30-60 minutes depending on your system.", nullptr));
        startSystemScanButton->setText(QCoreApplication::translate("ScanTypePage", "Start System Scan", nullptr));
        customScanTitle->setText(QCoreApplication::translate("ScanTypePage", "Custom Scan Description", nullptr));
        customScanLabel->setText(QCoreApplication::translate("ScanTypePage", "Custom Scan allows you to select specific locations to scan:\n"
"\n"
"- Choose specific files or folders\n"
"- Select drives to scan\n"
"- Customize scan settings\n"
"- Set scan priorities\n"
"- Choose scan depth\n"
"- Select file types to scan\n"
"\n"
"Scan time varies based on selected items.", nullptr));
        browseButton->setText(QCoreApplication::translate("ScanTypePage", "Browse...", nullptr));
        startCustomScanButton->setText(QCoreApplication::translate("ScanTypePage", "Start Custom Scan", nullptr));
        (void)ScanTypePage;
    } // retranslateUi

};

namespace Ui {
    class ScanTypePage: public Ui_ScanTypePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANTYPEPAGE_H
