// customfiledialog.cpp
#include "customfiledialog.h"

CustomFileDialog::CustomFileDialog(QWidget* parent) : QFileDialog(parent) {
    setOption(QFileDialog::DontUseNativeDialog, true);
    setWindowTitle("Select File or Directory to Scan");
    setViewMode(QFileDialog::Detail);
    setFileMode(QFileDialog::ExistingFile);
    setOption(QFileDialog::DontResolveSymlinks, true);
    
    // Create select directory button
    QVBoxLayout* layout = new QVBoxLayout();
    QWidget* extraWidget = new QWidget(this);
    QPushButton* selectDirButton = new QPushButton("Select Current Directory", extraWidget);
    layout->addWidget(selectDirButton);
    extraWidget->setLayout(layout);
    this->layout()->addWidget(extraWidget);
    
    connect(selectDirButton, &QPushButton::clicked, this, [this]() {
        // Get the current directory path
        QString dirPath = directory().absolutePath();
        // Set it as the selected file
        selectFile(dirPath);
        // Accept the dialog
        done(QDialog::Accepted);
    });
}

void CustomFileDialog::selectCurrentDirectory() {
    // This method is kept for compatibility but we're using the lambda above
    done(QDialog::Accepted);
}