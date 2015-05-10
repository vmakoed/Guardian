#include "guardiansmodel.h"

#include "database/database.h"
#include "file/fileFunctions.h"
#include "mount/getStoragesInfo.h"

#include <QDebug>

GuardiansModel::GuardiansModel(QObject *parent) : QObject(parent)
{

}

void GuardiansModel::scanDrives()
{
    USBInfo *info = new USBInfo;
    info->storagesCapacity = 0;
    getUSBInfo(info);

    char *inHex = new char[33];
    char *key = new char[17];
    char *name = new char[33];

    if(info->storagesCapacity == 0)
    {
        return;
    }
    else
    {
        for(int i = 0; i < info->storagesCapacity; i++)
        {
            if(extractInfo(info->driveLetters[i], "pass.guardian", name, key, inHex) == true)
            {
                if(checkGuardian(name, key, inHex) == true)
                {
                    mount(name);
                }
            }
        }
    }
}

void GuardiansModel::unmountAll()
{
    Database::exec("update guardian set mounted = 0");
}

void GuardiansModel::mount(char *name)
{
    QString *nameStr = new QString(name);
    Database::prepare("update guardian set mounted = 1 where guardianname = :guardianname;");
    Database::bind("guardianname", *nameStr);
    Database::exec();
}

QList<Guardian*>* GuardiansModel::guardians()
{
    QStringList *names = new QStringList;
    QList<bool> *states = new QList<bool>;

    names = Database::selectText("guardianname", "guardian");
    states = Database::selectBoolean("mounted", "guardian");

    QList<Guardian*> *guardiansList = new QList<Guardian*>;
    guardiansList->clear();

    for(int i = 0; i < names->size(); i++)
    {
        guardiansList->append(new Guardian(names->at(i)));

        if(states->at(i) == true)
        {
            guardiansList->at(i)->setState(MOUNTED);
        }
    }

    return guardiansList;
}

void GuardiansModel::addGuardian(QString drive, QString name)
{
    char *inHex = new char[33];
    char *key = new char[17];
    char *nameChar = new char[33];

    if(extractInfo(*(drive.toStdString().c_str()), "pass.guardian", nameChar, key, inHex) == true)
    {
        return;
    }

    CryptObject *cryptObject = new CryptObject;
    generateCryptObject(cryptObject);

    strcpy(nameChar, name.toStdString().c_str());

    writeToDrive(*(drive.toStdString().c_str()), "pass.guardian", nameChar,
                 cryptObject->key, cryptObject->inHex);

    writeInfoToDatabase(name, cryptObject->outHex);
}

void GuardiansModel::writeInfoToDatabase(QString name, char* outHex)
{
    QList<int> *guardians = new QList<int>;
    guardians = Database::selectInteger("guardianid", "guardian");

    Database::prepare("insert into guardian values(:guardianid, :guardianname, :guardiancode, :mounted);");

    if(guardians->isEmpty() == false)
    {
        Database::bind("guardianid", guardians->last() + 1);
    }
    else
    {
        Database::bind("guardianid", 0);
    }

    Database::bind("guardianname", name);
    Database::bind("guardiancode", outHex);
    Database::bind("mounted", 1);
    Database::exec();

    delete guardians;
}

bool GuardiansModel::checkGuardian(QString name, char *key, char *inHex)
{
    char *outHex = new char[33];
    getCodeFromDatabase(name, outHex);

    if(cryptTest(outHex, key, inHex) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GuardiansModel::getCodeFromDatabase(QString name, char *code)
{
    QString *condition = new QString("where guardianname = '");
    condition->append(name);
    condition->append("'");

    QStringList *outHex = new QStringList;
    outHex = Database::selectText("guardiancode", "guardian", condition);

    if(outHex->isEmpty())
    {
        return;
    }
    else
    {
        strcpy(code, outHex->at(0).toStdString().c_str());
    }
}

