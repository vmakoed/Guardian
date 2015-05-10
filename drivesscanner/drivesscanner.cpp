#include "drivesscanner.h"
#include <QDebug>

DrivesScanner::DrivesScanner(QObject *parent) : QObject(parent)
{

}

void DrivesScanner::scan()
{
    USBInfo *info = new USBInfo;
    info->storagesCapacity = 0;
    getUSBInfo(info);

    drivesCapacity = info->storagesCapacity;


    while(true)
    {
        info->storagesCapacity = 0;

        getUSBInfo(info);

        if(drivesCapacity != info->storagesCapacity)
        {
            drivesCapacity = info->storagesCapacity;
            emit drivesChanged();
        }

        Sleep(1000);
    }
}

