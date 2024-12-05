#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "signatureupdater.h"

// Worker class for threaded signature updates
class SignatureUpdateWorker : public QObject
{
    Q_OBJECT

public:
    explicit SignatureUpdateWorker(SignatureUpdater* updater) 
        : updater(updater), shouldStop(false) {}

public slots:
    void process() {
        if (!shouldStop) {
            updater->updateSignatures();
            emit finished(true);
        } else {
            emit finished(false);
        }
    }

    void stopUpdate() {
        shouldStop = true;
    }

signals:
    void finished(bool success);

private:
    SignatureUpdater* updater;
    bool shouldStop;
};

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsPage; }
QT_END_NAMESPACE

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();
    static void applyDarkMode(QWidget* widget, bool isDark);

private slots:
    void onBackButtonClicked();
    void onUpdateSignaturesClicked();
    void onDarkModeToggled(bool checked);
    void updateComplete(bool success);

signals:
    void backButtonClicked();
    void darkModeChanged(bool isDark);

private:
    Ui::SettingsPage *ui;
    SignatureUpdater* signatureUpdater;
    void loadSettings();
    void saveSettings();
};

#endif // SETTINGSPAGE_H