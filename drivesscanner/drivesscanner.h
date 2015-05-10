#ifndef DRIVESSCANNER_H
#define DRIVESSCANNER_H

#include <QObject>

#include "file/fileFunctions.h"
#include "mount/getStoragesInfo.h"

class DrivesScanner : public QObject
{
    Q_OBJECT
private:
    int drivesCapacity;

public:
    explicit DrivesScanner(QObject *parent = 0);
    void scan();

signals:
    void drivesChanged();
    void checked();

public slots:
};

#endif // DRIVESSCANNER_H
