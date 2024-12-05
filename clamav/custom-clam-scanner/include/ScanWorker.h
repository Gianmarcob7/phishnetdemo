// ScanWorker.h
#ifndef SCANWORKER_H
#define SCANWORKER_H

#include <QObject>
#include <QString>
#include "customscan.h"
#include "systemscan.h"
#include "quickscan.h"

class ScanWorker : public QObject {
    Q_OBJECT
public:
    explicit ScanWorker(QObject* parent = nullptr);
    ~ScanWorker();
    
    void setScanPath(const QString& path);
    void setScanType(const QString& type);

public slots:
    void doScan();

signals:
    void scanComplete(int filesScanned, int threatsFound);
    void scanProgress(int filesScanned);

private:
    ClamAVTester* customScanner;
    SystemScan* systemScanner;
    QuickScan* quickScanner;
    QString scanPath;
    QString scanType;
};

#endif // SCANWORKER_H