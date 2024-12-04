/********************************************************************************
** Form generated from reading UI file 'lastscanpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LASTSCANPAGE_H
#define UI_LASTSCANPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LastScanPage
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *titleLabel;
    QFrame *infoFrame;
    QVBoxLayout *infoLayout;
    QLabel *dateTimeLabel;
    QLabel *scanTypeLabel;
    QLabel *durationLabel;
    QLabel *filesScannedLabel;
    QLabel *threatsFoundLabel;
    QLabel *statusLabel;
    QHBoxLayout *buttonLayout;
    QPushButton *rescanButton;
    QPushButton *viewDetailsButton;

    void setupUi(QWidget *LastScanPage)
    {
        if (LastScanPage->objectName().isEmpty())
            LastScanPage->setObjectName(QString::fromUtf8("LastScanPage"));
        LastScanPage->resize(222, 388);
        verticalLayout = new QVBoxLayout(LastScanPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        backButton = new QPushButton(LastScanPage);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        verticalLayout->addWidget(backButton);

        titleLabel = new QLabel(LastScanPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Serif"));
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        infoFrame = new QFrame(LastScanPage);
        infoFrame->setObjectName(QString::fromUtf8("infoFrame"));
        infoFrame->setFrameShape(QFrame::StyledPanel);
        infoLayout = new QVBoxLayout(infoFrame);
        infoLayout->setObjectName(QString::fromUtf8("infoLayout"));
        dateTimeLabel = new QLabel(infoFrame);
        dateTimeLabel->setObjectName(QString::fromUtf8("dateTimeLabel"));

        infoLayout->addWidget(dateTimeLabel);

        scanTypeLabel = new QLabel(infoFrame);
        scanTypeLabel->setObjectName(QString::fromUtf8("scanTypeLabel"));

        infoLayout->addWidget(scanTypeLabel);

        durationLabel = new QLabel(infoFrame);
        durationLabel->setObjectName(QString::fromUtf8("durationLabel"));

        infoLayout->addWidget(durationLabel);

        filesScannedLabel = new QLabel(infoFrame);
        filesScannedLabel->setObjectName(QString::fromUtf8("filesScannedLabel"));

        infoLayout->addWidget(filesScannedLabel);

        threatsFoundLabel = new QLabel(infoFrame);
        threatsFoundLabel->setObjectName(QString::fromUtf8("threatsFoundLabel"));

        infoLayout->addWidget(threatsFoundLabel);

        statusLabel = new QLabel(infoFrame);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        infoLayout->addWidget(statusLabel);


        verticalLayout->addWidget(infoFrame);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        rescanButton = new QPushButton(LastScanPage);
        rescanButton->setObjectName(QString::fromUtf8("rescanButton"));
        rescanButton->setFont(font);

        buttonLayout->addWidget(rescanButton);

        viewDetailsButton = new QPushButton(LastScanPage);
        viewDetailsButton->setObjectName(QString::fromUtf8("viewDetailsButton"));
        viewDetailsButton->setFont(font);

        buttonLayout->addWidget(viewDetailsButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(LastScanPage);

        QMetaObject::connectSlotsByName(LastScanPage);
    } // setupUi

    void retranslateUi(QWidget *LastScanPage)
    {
        backButton->setStyleSheet(QCoreApplication::translate("LastScanPage", "\n"
"       QPushButton {\n"
"           background-color: #e0e0e0;\n"
"           border: 1px solid #c0c0c0;\n"
"           border-radius: 3px;\n"
"           padding: 5px 15px;\n"
"       }\n"
"       QPushButton:hover {\n"
"           background-color: #d0d0d0;\n"
"       }\n"
"      ", nullptr));
        backButton->setText(QCoreApplication::translate("LastScanPage", "Back", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("LastScanPage", "\n"
"       QLabel {\n"
"           font-size: 18px;\n"
"           color: #cc0000;\n"
"           padding: 10px;\n"
"       }\n"
"      ", nullptr));
        titleLabel->setText(QCoreApplication::translate("LastScanPage", "Last Scan Results", nullptr));
        infoFrame->setStyleSheet(QCoreApplication::translate("LastScanPage", "\n"
"       QFrame {\n"
"           background-color: #f0f0f0;\n"
"           border: 1px solid #c0c0c0;\n"
"           border-radius: 4px;\n"
"           padding: 10px;\n"
"       }\n"
"       QLabel {\n"
"           font-size: 14px;\n"
"           color: #333333;\n"
"           padding: 5px;\n"
"       }\n"
"      ", nullptr));
        rescanButton->setStyleSheet(QCoreApplication::translate("LastScanPage", "\n"
"         QPushButton {\n"
"             background-color: #cc0000;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 8px 16px;\n"
"             border-radius: 4px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #b30000;\n"
"         }\n"
"        ", nullptr));
        rescanButton->setText(QCoreApplication::translate("LastScanPage", "Rescan", nullptr));
        viewDetailsButton->setStyleSheet(QCoreApplication::translate("LastScanPage", "\n"
"         QPushButton {\n"
"             background-color: #666666;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 8px 16px;\n"
"             border-radius: 4px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #555555;\n"
"         }\n"
"        ", nullptr));
        viewDetailsButton->setText(QCoreApplication::translate("LastScanPage", "View Details", nullptr));
        (void)LastScanPage;
    } // retranslateUi

};

namespace Ui {
    class LastScanPage: public Ui_LastScanPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LASTSCANPAGE_H
