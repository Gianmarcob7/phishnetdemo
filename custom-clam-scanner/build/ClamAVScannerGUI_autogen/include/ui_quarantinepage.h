/********************************************************************************
** Form generated from reading UI file 'quarantinepage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUARANTINEPAGE_H
#define UI_QUARANTINEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuarantinePage
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *titleLabel;
    QListWidget *fileList;
    QHBoxLayout *buttonLayout;
    QPushButton *deleteButton;
    QPushButton *keepButton;

    void setupUi(QWidget *QuarantinePage)
    {
        if (QuarantinePage->objectName().isEmpty())
            QuarantinePage->setObjectName(QString::fromUtf8("QuarantinePage"));
        QuarantinePage->resize(800, 600);
        verticalLayout = new QVBoxLayout(QuarantinePage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        backButton = new QPushButton(QuarantinePage);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Serif"));
        backButton->setFont(font);

        verticalLayout->addWidget(backButton);

        titleLabel = new QLabel(QuarantinePage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        fileList = new QListWidget(QuarantinePage);
        fileList->setObjectName(QString::fromUtf8("fileList"));

        verticalLayout->addWidget(fileList);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        deleteButton = new QPushButton(QuarantinePage);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setFont(font);

        buttonLayout->addWidget(deleteButton);

        keepButton = new QPushButton(QuarantinePage);
        keepButton->setObjectName(QString::fromUtf8("keepButton"));
        keepButton->setFont(font);

        buttonLayout->addWidget(keepButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(QuarantinePage);

        QMetaObject::connectSlotsByName(QuarantinePage);
    } // setupUi

    void retranslateUi(QWidget *QuarantinePage)
    {
        backButton->setStyleSheet(QCoreApplication::translate("QuarantinePage", "\n"
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
        backButton->setText(QCoreApplication::translate("QuarantinePage", "Back", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("QuarantinePage", "\n"
"       QLabel {\n"
"           font-size: 18px;\n"
"           color: #cc0000;\n"
"           padding: 10px;\n"
"       }\n"
"      ", nullptr));
        titleLabel->setText(QCoreApplication::translate("QuarantinePage", "Quarantined Files", nullptr));
        fileList->setStyleSheet(QCoreApplication::translate("QuarantinePage", "\n"
"       QListWidget {\n"
"           background-color: #f0f0f0;\n"
"           border: 1px solid #c0c0c0;\n"
"           border-radius: 4px;\n"
"       }\n"
"       QListWidget::item {\n"
"           padding: 8px;\n"
"           border-bottom: 1px solid #e0e0e0;\n"
"       }\n"
"       QListWidget::item:selected {\n"
"           background-color: #cc0000;\n"
"           color: white;\n"
"       }\n"
"      ", nullptr));
        deleteButton->setStyleSheet(QCoreApplication::translate("QuarantinePage", "\n"
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
"         QPushButton:disabled {\n"
"             background-color: #cccccc;\n"
"         }\n"
"        ", nullptr));
        deleteButton->setText(QCoreApplication::translate("QuarantinePage", "Delete File", nullptr));
        keepButton->setStyleSheet(QCoreApplication::translate("QuarantinePage", "\n"
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
"         QPushButton:disabled {\n"
"             background-color: #cccccc;\n"
"         }\n"
"        ", nullptr));
        keepButton->setText(QCoreApplication::translate("QuarantinePage", "Keep in Quarantine", nullptr));
        (void)QuarantinePage;
    } // retranslateUi

};

namespace Ui {
    class QuarantinePage: public Ui_QuarantinePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUARANTINEPAGE_H
