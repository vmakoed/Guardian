#include "drivesscanner.h"

DrivesScanner::DrivesScanner(QObject *parent) : QObject(parent)
{

}

void DrivesScanner::scan(char *drives)
{
    USBInfo *info = new USBInfo;
    getUSBInfo(info);

    if(info->storagesCapacity == 0)
    {
        drives[0] = '\0';
        return;
    }

    int i;
    for(i = 0; i < info->storagesCapacity; i++)
    {
        drives[i] = info->driveLetters[i];
    }

    drives[i] = '\0';
}

QString *DrivesScanner::getStorageName(char drive)
{
    USBInfo *info = new USBInfo;
    getUSBInfo(info);

    QString *name = new QString;

    for(int i = 0; i < info->storagesCapacity; i++)
    {
        if(info->driveLetters[i] == drive)
        {
            name->append(QString::fromLatin1(info->productNames[i]));
            break;
        }
    }

    if(name->isEmpty())
    {
        return nullptr;
    }
    else
    {
        return name;
    }
}

void DrivesScanner::startScan()
{
    USBInfo *info = new USBInfo;
    info->storagesCapacity = 0;
    info->driveLetters[0] = '\0';
    getUSBInfo(info);

    drivesCapacity = info->storagesCapacity;
    char *oldDrives = new char[MAX_NUM_OF_STORAGES];
    strcpy(oldDrives, info->driveLetters);

    while(true)
    {
        USBInfo *infoN = new USBInfo;
        infoN->storagesCapacity = 0;

        getUSBInfo(infoN);

        if(drivesCapacity > infoN->storagesCapacity)
        {
            int alteredDrivesCapacity = 0;
            char *alteredDrives = new char[MAX_NUM_OF_DRIVES];

            for(int i = 0; i < strlen(oldDrives); i++)
            {
                char drive = oldDrives[i];

                if(strchr(infoN->driveLetters, drive) == nullptr)
                {
                    alteredDrives[alteredDrivesCapacity] = drive;
                    alteredDrivesCapacity++;
                }
            }

            emit drivesUnmounted(alteredDrives, alteredDrivesCapacity);

            strcpy(oldDrives, infoN->driveLetters);
            drivesCapacity = infoN->storagesCapacity;
        }
        else if(drivesCapacity < infoN->storagesCapacity)
        {
            int alteredDrivesCapacity = 0;
            char *alteredDrives = new char[MAX_NUM_OF_DRIVES];

            for(int i = 0; i < infoN->storagesCapacity; i++)
            {
                char drive = infoN->driveLetters[i];

                if(strchr(oldDrives, drive) == nullptr)
                {
                    alteredDrives[alteredDrivesCapacity] = drive;
                    alteredDrivesCapacity++;
                }
            }

            emit drivesMounted(alteredDrives, alteredDrivesCapacity);

            strcpy(oldDrives, infoN->driveLetters);
            drivesCapacity = infoN->storagesCapacity;
        }

        Sleep(500);
    }
}
