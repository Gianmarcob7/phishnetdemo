/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *history_button;
    QPushButton *lastscan_button;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_9;
    QPushButton *schedule_button;
    QLabel *label_8;
    QPushButton *scan_button;
    QLabel *label_4;
    QPushButton *quar_button;
    QLabel *titlelabel;
    QLabel *explainlabel;
    QPushButton *settings_button;
    QPushButton *close_button;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(526, 462);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        history_button = new QPushButton(centralwidget);
        history_button->setObjectName(QString::fromUtf8("history_button"));
        history_button->setGeometry(QRect(360, 100, 91, 81));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(57, 79, 53, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush3(QColor(97, 105, 93, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        history_button->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Serif"));
        font.setPointSize(11);
        font.setBold(true);
        history_button->setFont(font);
        history_button->setCursor(QCursor(Qt::PointingHandCursor));
        history_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(200, 200, 200, 50);  /* Light grey background on hover */\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/icons/history scan"), QSize(), QIcon::Normal, QIcon::Off);
        history_button->setIcon(icon);
        history_button->setIconSize(QSize(75, 75));
        lastscan_button = new QPushButton(centralwidget);
        lastscan_button->setObjectName(QString::fromUtf8("lastscan_button"));
        lastscan_button->setGeometry(QRect(290, 250, 91, 81));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        lastscan_button->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Serif"));
        font1.setBold(true);
        lastscan_button->setFont(font1);
        lastscan_button->setCursor(QCursor(Qt::PointingHandCursor));
        lastscan_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(200, 200, 200, 50);  /* Light grey background on hover */\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/icons/last scan "), QSize(), QIcon::Normal, QIcon::Off);
        lastscan_button->setIcon(icon1);
        lastscan_button->setIconSize(QSize(75, 75));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(370, 190, 81, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_7->setPalette(palette2);
        label_7->setFont(font);
        label_7->setAutoFillBackground(false);
        label_7->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(90, 190, 51, 20));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_6->setPalette(palette3);
        label_6->setFont(font);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(300, 330, 61, 51));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_9->setPalette(palette4);
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);
        schedule_button = new QPushButton(centralwidget);
        schedule_button->setObjectName(QString::fromUtf8("schedule_button"));
        schedule_button->setGeometry(QRect(210, 100, 91, 81));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush);
        schedule_button->setPalette(palette5);
        schedule_button->setFont(font);
        schedule_button->setCursor(QCursor(Qt::PointingHandCursor));
        schedule_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(200, 200, 200, 50);  /* Light grey background on hover */\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/icons/sch scan"), QSize(), QIcon::Normal, QIcon::Off);
        schedule_button->setIcon(icon2);
        schedule_button->setIconSize(QSize(75, 75));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(130, 330, 121, 51));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_8->setPalette(palette6);
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);
        scan_button = new QPushButton(centralwidget);
        scan_button->setObjectName(QString::fromUtf8("scan_button"));
        scan_button->setGeometry(QRect(60, 100, 91, 81));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Button, brush);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush);
        scan_button->setPalette(palette7);
        scan_button->setFont(font1);
        scan_button->setCursor(QCursor(Qt::PointingHandCursor));
        scan_button->setMouseTracking(true);
        scan_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(200, 200, 200, 50);  /* Light grey background on hover */\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/icons/scan"), QSize(), QIcon::Normal, QIcon::Off);
        scan_button->setIcon(icon3);
        scan_button->setIconSize(QSize(60, 60));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 180, 91, 51));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_4->setPalette(palette8);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        quar_button = new QPushButton(centralwidget);
        quar_button->setObjectName(QString::fromUtf8("quar_button"));
        quar_button->setGeometry(QRect(140, 250, 91, 81));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Button, brush);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush);
        quar_button->setPalette(palette9);
        quar_button->setFont(font1);
        quar_button->setCursor(QCursor(Qt::PointingHandCursor));
        quar_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(200, 200, 200, 50);  /* Light grey background on hover */\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/icons/quarfiles"), QSize(), QIcon::Normal, QIcon::Off);
        quar_button->setIcon(icon4);
        quar_button->setIconSize(QSize(75, 75));
        titlelabel = new QLabel(centralwidget);
        titlelabel->setObjectName(QString::fromUtf8("titlelabel"));
        titlelabel->setGeometry(QRect(20, 10, 201, 20));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        titlelabel->setPalette(palette10);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Serif"));
        font2.setPointSize(15);
        font2.setBold(true);
        titlelabel->setFont(font2);
        explainlabel = new QLabel(centralwidget);
        explainlabel->setObjectName(QString::fromUtf8("explainlabel"));
        explainlabel->setGeometry(QRect(20, 30, 411, 18));
        QPalette palette11;
        QBrush brush4(QColor(94, 92, 100, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        explainlabel->setPalette(palette11);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Serif"));
        font3.setPointSize(8);
        explainlabel->setFont(font3);
        settings_button = new QPushButton(centralwidget);
        settings_button->setObjectName(QString::fromUtf8("settings_button"));
        settings_button->setGeometry(QRect(430, 410, 88, 26));
        QPalette palette12;
        QBrush brush5(QColor(255, 255, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette12.setBrush(QPalette::Active, QPalette::Button, brush5);
        QBrush brush6(QColor(239, 239, 239, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette12.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette12.setBrush(QPalette::Disabled, QPalette::Button, brush5);
        settings_button->setPalette(palette12);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Serif"));
        settings_button->setFont(font4);
        QIcon icon5;
        QString iconThemeName = QString::fromUtf8("preferences-system");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        settings_button->setIcon(icon5);
        close_button = new QPushButton(centralwidget);
        close_button->setObjectName(QString::fromUtf8("close_button"));
        close_button->setGeometry(QRect(20, 410, 88, 26));
        close_button->setFont(font4);
        close_button->setCursor(QCursor(Qt::PointingHandCursor));
        close_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"       border: none;\n"
"       background-color: transparent;\n"
"       color: #cc0000;\n"
"       padding: 5px 15px;\n"
"       border-radius: 3px;\n"
"   }\n"
"\n"
"   QPushButton:hover {\n"
"       background-color: rgba(200, 200, 200, 50);\n"
"   }"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        history_button->setText(QString());
        lastscan_button->setText(QString());
#if QT_CONFIG(tooltip)
        label_7->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_7->setText(QCoreApplication::translate("MainWindow", "History", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Scan", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Last\n"
" Scan", nullptr));
        schedule_button->setText(QString());
#if QT_CONFIG(tooltip)
        label_8->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("MainWindow", "Quarantined\n"
"Files", nullptr));
        scan_button->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Schedule\n"
"Scan", nullptr));
        quar_button->setText(QString());
        titlelabel->setText(QCoreApplication::translate("MainWindow", "PhishNet AntiVirus", nullptr));
        explainlabel->setText(QCoreApplication::translate("MainWindow", "Welcome to PhishNet AntiVirus - Protect your system from malware. ", nullptr));
        settings_button->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        close_button->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
