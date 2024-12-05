/********************************************************************************
** Form generated from reading UI file 'settingspage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSPAGE_H
#define UI_SETTINGSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsPage
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *titleLabel;
    QPushButton *updateButton;
    QCheckBox *darkModeCheck;
    QLabel *clamVersionLabel;
    QLabel *qtVersionLabel;
    QLabel *phishnetVersionLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SettingsPage)
    {
        if (SettingsPage->objectName().isEmpty())
            SettingsPage->setObjectName(QString::fromUtf8("SettingsPage"));
        SettingsPage->resize(400, 400);
        verticalLayout = new QVBoxLayout(SettingsPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        backButton = new QPushButton(SettingsPage);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        verticalLayout->addWidget(backButton);

        titleLabel = new QLabel(SettingsPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        updateButton = new QPushButton(SettingsPage);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        verticalLayout->addWidget(updateButton);

        darkModeCheck = new QCheckBox(SettingsPage);
        darkModeCheck->setObjectName(QString::fromUtf8("darkModeCheck"));

        verticalLayout->addWidget(darkModeCheck);

        clamVersionLabel = new QLabel(SettingsPage);
        clamVersionLabel->setObjectName(QString::fromUtf8("clamVersionLabel"));
        clamVersionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(clamVersionLabel);

        qtVersionLabel = new QLabel(SettingsPage);
        qtVersionLabel->setObjectName(QString::fromUtf8("qtVersionLabel"));
        qtVersionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(qtVersionLabel);

        phishnetVersionLabel = new QLabel(SettingsPage);
        phishnetVersionLabel->setObjectName(QString::fromUtf8("phishnetVersionLabel"));
        phishnetVersionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(phishnetVersionLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SettingsPage);

        QMetaObject::connectSlotsByName(SettingsPage);
    } // setupUi

    void retranslateUi(QWidget *SettingsPage)
    {
        backButton->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
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
        backButton->setText(QCoreApplication::translate("SettingsPage", "Back", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
"       QLabel {\n"
"           font-size: 20px;\n"
"           color: #cc0000;\n"
"           padding: 10px;\n"
"           font-weight: bold;\n"
"       }\n"
"      ", nullptr));
        titleLabel->setText(QCoreApplication::translate("SettingsPage", "Settings", nullptr));
        updateButton->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
"       QPushButton {\n"
"           background-color: #cc0000;\n"
"           color: white;\n"
"           border: none;\n"
"           padding: 8px 16px;\n"
"           border-radius: 4px;\n"
"           font-size: 14px;\n"
"       }\n"
"       QPushButton:hover {\n"
"           background-color: #b30000;\n"
"       }\n"
"      ", nullptr));
        updateButton->setText(QCoreApplication::translate("SettingsPage", "Update Virus Signatures", nullptr));
        darkModeCheck->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
"       QCheckBox {\n"
"           padding: 8px;\n"
"           font-size: 14px;\n"
"       }\n"
"       QCheckBox::indicator {\n"
"           width: 18px;\n"
"           height: 18px;\n"
"           border-radius: 3px;\n"
"       }\n"
"       QCheckBox::indicator:unchecked {\n"
"           border: 1px solid #c0c0c0;\n"
"       }\n"
"       QCheckBox::indicator:checked {\n"
"           background-color: #cc0000;\n"
"           border: 1px solid #cc0000;\n"
"       }\n"
"      ", nullptr));
        darkModeCheck->setText(QCoreApplication::translate("SettingsPage", "Enable Dark Mode", nullptr));
        clamVersionLabel->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
"       QLabel {\n"
"           font-size: 14px;\n"
"           padding: 5px;\n"
"       }\n"
"      ", nullptr));
        qtVersionLabel->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
"       QLabel {\n"
"           font-size: 14px;\n"
"           padding: 5px;\n"
"       }\n"
"      ", nullptr));
        phishnetVersionLabel->setStyleSheet(QCoreApplication::translate("SettingsPage", "\n"
"       QLabel {\n"
"           font-size: 14px;\n"
"           padding: 5px;\n"
"       }\n"
"      ", nullptr));
        (void)SettingsPage;
    } // retranslateUi

};

namespace Ui {
    class SettingsPage: public Ui_SettingsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSPAGE_H
