#ifndef DRIVESSCANNER_H
#define DRIVESSCANNER_H

#include <QObject>

#include "drivesscanner/getStoragesInfo.h"

#define MAX_NUM_OF_DRIVES   20

class DrivesScanner : public QObject
{
    Q_OBJECT

private:
    int drivesCapacity;

public:
    explicit DrivesScanner(QObject *parent = 0);
    void scan(char *drives);
    QString *getStorageName(char drive);

signals:   
    void drivesMounted(char *alteredDrives, int alteredDrivesCapacity);
    void drivesUnmounted(char *alteredDrives, int alteredDrivesCapacity);

public slots:
    void startScan();
};

#endif // DRIVESSCANNER_H
