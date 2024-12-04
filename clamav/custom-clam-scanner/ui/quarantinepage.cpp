#include "quarantinepage.h"
#include "ui_quarantinepage.h"
#include <QMessageBox>
#include <QDateTime>
#include <QPainter>
#include <QPainterPath>
#include <filesystem>
#include <QDir>

namespace fs = std::filesystem;

QuarantinePage::QuarantinePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QuarantinePage)
{
    ui->setupUi(this);

    // Connect signals
    connect(ui->backButton, &QPushButton::clicked, this, &QuarantinePage::onBackButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &QuarantinePage::onDeleteButtonClicked);
    connect(ui->keepButton, &QPushButton::clicked, this, &QuarantinePage::onKeepButtonClicked);
    connect(ui->fileList, &QListWidget::itemSelectionChanged, this, &QuarantinePage::onItemSelectionChanged);

    // Initial setup
    loadQuarantinedFiles();
    updateButtons();
}

QuarantinePage::~QuarantinePage()
{
    delete ui;
}

void QuarantinePage::setMessageBoxStyle(QMessageBox* msgBox)
{
    QPixmap customIcon(32, 32);
    customIcon.fill(Qt::transparent);
    QPainter painter(&customIcon);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addEllipse(2, 2, 28, 28);
    painter.setPen(QPen(QColor("#cc0000"), 2));
    painter.setBrush(QColor("#f0f0f0"));
    painter.drawPath(path);

    msgBox->setIconPixmap(customIcon);
    msgBox->setStyleSheet(
        "QMessageBox { background-color: #f0f0f0; }"
        "QMessageBox QLabel { color: #333333; font-family: Serif; font-size: 12px; padding: 10px; }"
        "QPushButton { background-color: #666666; color: white; border: none; padding: 6px 12px; "
        "              border-radius: 4px; font-family: Serif; font-weight: bold; min-width: 80px; }"
        "QPushButton:hover { background-color: #555555; }"
        "QPushButton:pressed { background-color: #444444; }"
    );
}

void QuarantinePage::loadQuarantinedFiles()
{
    ui->fileList->clear();
    const std::string quarantinePath = "/home/gianmarco/Downloads/clamav/clamav/custom-clam-scanner/build/Quarantine";
    
    try {
        for (const auto& entry : fs::directory_iterator(quarantinePath)) {
            if (fs::is_regular_file(entry)) {
                QString filePath = QString::fromStdString(entry.path().string());
                QString fileName = QString::fromStdString(entry.path().filename().string());
                
                QListWidgetItem* item = new QListWidgetItem(fileName);
                item->setData(Qt::UserRole, filePath); // Store full path for later use
                ui->fileList->addItem(item);
            }
        }
    } catch (const fs::filesystem_error& e) {
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Error");
        msgBox->setText("Error accessing quarantine directory: " + QString(e.what()));
        setMessageBoxStyle(msgBox);
        msgBox->exec();
        delete msgBox;
    }
}

void QuarantinePage::onDeleteButtonClicked()
{
    auto selectedItems = ui->fileList->selectedItems();
    if (selectedItems.isEmpty()) return;

    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Confirm Deletion");
    msgBox->setText("Are you sure you want to permanently delete the selected file(s)?");
    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox->setDefaultButton(QMessageBox::No);
    setMessageBoxStyle(msgBox);

    if (msgBox->exec() == QMessageBox::Yes) {
        for(QListWidgetItem* item : selectedItems) {
            QString filePath = item->data(Qt::UserRole).toString();
            QFile file(filePath);
            if (file.remove()) {
                delete ui->fileList->takeItem(ui->fileList->row(item));
            } else {
                QMessageBox* errorBox = new QMessageBox(this);
                errorBox->setWindowTitle("Error");
                errorBox->setText("Failed to delete file: " + filePath);
                setMessageBoxStyle(errorBox);
                errorBox->exec();
                delete errorBox;
            }
        }
    }
    
    delete msgBox;
    updateButtons();
}

void QuarantinePage::onKeepButtonClicked()
{
    auto selectedItems = ui->fileList->selectedItems();
    if (selectedItems.isEmpty()) return;

    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Keep Files");
    msgBox->setText("Files will remain in quarantine for safety.");
    msgBox->setStandardButtons(QMessageBox::Ok);
    setMessageBoxStyle(msgBox);
    msgBox->exec();
    delete msgBox;

    updateButtons();
}

void QuarantinePage::updateButtons()
{
    bool hasSelection = !ui->fileList->selectedItems().isEmpty();
    ui->deleteButton->setEnabled(hasSelection);
    ui->keepButton->setEnabled(hasSelection);
}

void QuarantinePage::onItemSelectionChanged()
{
    updateButtons();
}

void QuarantinePage::onBackButtonClicked()
{
    emit backButtonClicked();
}