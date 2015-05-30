#include "datamanager.h"
#include <QDebug>

QList<Item *> *DataManager::getItems()
{
    QStringList *names = Database::selectStringList("name", "item");
    QStringList *paths = Database::selectStringList("path", "item");
    QList<int> *types = Database::selectIntegerList("type", "item");
    QList<bool> *states = Database::selectBooleanList("unlocked", "item");
    QList<bool> *protection = Database::selectBooleanList("protected", "item");
    QList<int> *guardianIds = Database::selectIntegerList("guardian", "item");

    QList<ITEM_TYPE> *itemsTypesList = new QList<ITEM_TYPE>;
    for(auto type : *types)
    {
        switch(type)
        {
        case 0:
            itemsTypesList->append(ITEM_FILE);
            break;
        case 1:
            itemsTypesList->append(ITEM_FOLDER);
            break;
        }
    }

    QList<ITEM_GUARDIAN_STATE> *itemsStatesList = new QList<ITEM_GUARDIAN_STATE>;
    for(auto state : *states)
    {
        switch(state)
        {
        case true:
            itemsStatesList->append(UNLOCKED);
            break;
        case false:
            itemsStatesList->append(LOCKED);
            break;
        }
    }

    QStringList *guardianNames = new QStringList;
    for(auto id : *guardianIds)
    {
        guardianNames->append(*(Database::selectString("name", "guardian", Database::where("id", id))));
    }

    QList<Item*> *itemsList = new QList<Item*>;

    for(int i = 0; i < names->size(); i++)
    {
        itemsList->append(new Item(names->at(i), paths->at(i), itemsTypesList->at(i), itemsStatesList->at(i), protection->at(i), guardianNames->at(i)));
    }

    return itemsList;
}

QList<Item *> *DataManager::getItems(ITEM_TYPE type)
{
    int typeInt;

    if(type == ITEM_FILE)
    {
        typeInt = 0;
    }
    else if(type == ITEM_FOLDER)
    {
        typeInt = 1;
    }
    else if(type == ITEM_APP)
    {
        typeInt = 2;
    }

    QStringList *names= Database::selectStringList("name", "item", Database::where("type", typeInt));
    QStringList *paths = Database::selectStringList("path", "item", Database::where("type", typeInt));
    QList<bool> *states = Database::selectBooleanList("unlocked", "item", Database::where("type", typeInt));
    QList<bool> *protection = Database::selectBooleanList("protected", "item", Database::where("type", typeInt));
    QList<int> *guardianIds = Database::selectIntegerList("guardian", "item", Database::where("type", typeInt));

    QList<ITEM_GUARDIAN_STATE> *itemsStatesList = new QList<ITEM_GUARDIAN_STATE>;

    for(int i = 0; i < guardianIds->size(); i++)
    {
        if(DataManager::isGuardianMounted(*(Database::selectString("name", "guardian", Database::where("id", guardianIds->at(i))))))
        {
            itemsStatesList->append(UNLOCKED);
        }
        else
        {
            itemsStatesList->append(LOCKED);
        }
    }

    QStringList *guardianNames = new QStringList;
    for(auto id : *guardianIds)
    {
        guardianNames->append(*(Database::selectString("name", "guardian", Database::where("id", id))));
    }

    QList<Item*> *itemsList = new QList<Item*>;

    for(int i = 0; i < names->size(); i++)
    {
        itemsList->append(new Item(names->at(i), paths->at(i), type, itemsStatesList->at(i), protection->at(i), guardianNames->at(i)));
    }

    return itemsList;
}

QList<Item *> *DataManager::getItems(QString guardianName)
{
    int guardianId = Database::selectInteger("id", "guardian", Database::where("name", guardianName));

    QStringList *names = Database::selectStringList("name", "item", Database::where("guardian", guardianId));
    QStringList *paths = Database::selectStringList("path", "item", Database::where("guardian", guardianId));
    QList<int> *types = Database::selectIntegerList("type", "item", Database::where("guardian", guardianId));
    QList<bool> *protection = Database::selectBooleanList("protected", "item", Database::where("guardian", guardianId));
    QList<bool> *states = Database::selectBooleanList("unlocked", "item", Database::where("guardian", guardianId));

    QList<ITEM_TYPE> *itemsTypesList = new QList<ITEM_TYPE>;
    for(auto type : *types)
    {
        switch(type)
        {
        case 0:
            itemsTypesList->append(ITEM_FILE);
            break;

        case 1:
            itemsTypesList->append(ITEM_FOLDER);
            break;

        case 2:
            itemsTypesList->append(ITEM_APP);
            break;
        }
    }

    QList<ITEM_GUARDIAN_STATE> *itemsStatesList = new QList<ITEM_GUARDIAN_STATE>;

    if(DataManager::isGuardianMounted(guardianName) == true)
    {
        for(int i = 0; i < states->size(); i++)
        {
            itemsStatesList->append(UNLOCKED);
        }
    }
    else
    {
        for(int i = 0; i < states->size(); i++)
        {
            itemsStatesList->append(LOCKED);
        }
    }

    QList<Item*> *itemsList = new QList<Item*>;

    for(int i = 0; i < names->size(); i++)
    {
        itemsList->append(new Item(names->at(i), paths->at(i), itemsTypesList->at(i), itemsStatesList->at(i), protection->at(i), guardianName));
    }

    return itemsList;
}

QString *DataManager::getSystemKeyName()
{
    return Database::selectString("name", "guardian", Database::where("id", Database::selectInteger("guardian", "systemkey")));
}

Item *DataManager::getSystemItem()
{
    return new Item("SYSTEM", "", ITEM_APP, UNLOCKED, Database::selectBoolean("protected", "systemkey"),
                    *(Database::selectString("name", "guardian",
                                           Database::where("id", Database::selectInteger("guardian", "systemkey")))));
}

QList<Guardian *> *DataManager::getGuardians()
{
    QStringList *names = Database::selectStringList("name", "guardian");
    QList<bool> *states = Database::selectBooleanList("mounted", "guardian");
    QStringList *drives = Database::selectStringList("drive", "guardian");

    QList<GUARDIAN_STATE> *guardianStates = new QList<GUARDIAN_STATE>;
    for(auto state : *states)
    {
        switch(state)
        {
        case true:
            guardianStates->append(MOUNTED);
            break;
        case false:
            guardianStates->append(UNMOUNTED);
            break;
        }
    }

    QList<Guardian*> *guardiansList = new QList<Guardian*>;


    for(int i = 0; i < names->size(); i++)
    {
        char drive = *(drives->at(i).toStdString().c_str());
        guardiansList->append(new Guardian(names->at(i), guardianStates->at(i), drive));
    }

    return guardiansList;
}

QList<Guardian *> *DataManager::getGuardians(GUARDIAN_STATE state)
{
    bool stateBool;

    switch(state)
    {
    case MOUNTED:
        stateBool = true;
        break;

    case UNMOUNTED:
        stateBool = false;
        break;
    }

    QStringList *names = Database::selectStringList("name", "guardian", Database::where("mounted", stateBool));
    QStringList *drives = Database::selectStringList("drive", "guardian", Database::where("mounted", stateBool));

    QList<Guardian*> *guardiansList = new QList<Guardian*>;

    for(int i = 0; i < names->size(); i++)
    {
        char drive = *(drives->at(i).toStdString().c_str());
        guardiansList->append(new Guardian(names->at(i), state, drive));
    }

    return guardiansList;
}

QString DataManager::getGuardianCode(QString guardianName)
{
    return *(Database::selectString("code", "guardian", Database::where("name", guardianName)));
}

QString *DataManager::getGuardianName(char drive)
{
    QString *guardianName = new QString;
    guardianName = Database::selectString("name", "guardian", Database::where("drive", *(new QString(drive))));

    if(guardianName->isEmpty() == false)
    {
        return guardianName;
    }
    else
    {
        return nullptr;
    }
}

GUARDIAN_STATE DataManager::getGuardianState(QString guardianName)
{
    if(Database::selectBoolean("mounted", "guardian", Database::where("name", guardianName)))
    {
        return MOUNTED;
    }
    else
    {
        return UNMOUNTED;
    }
}

void DataManager::setItemsState(QList<Item *> *items, ITEM_GUARDIAN_STATE state)
{
    bool isUnlocked;

    switch(state)
    {
    case UNLOCKED:
        isUnlocked = true;
        break;
    case LOCKED:
        isUnlocked = false;
        break;
    }

    for(auto item : *items)
    {
        Database::prepare("update item set unlocked = :unlocked where path = :path");
        Database::bind("unlocked", isUnlocked);
        Database::bind("path", item->getPath());
        Database::exec();
    }
}

void DataManager::setGuardianState(QString *guardianName, GUARDIAN_STATE state, char drive)
{
    bool isMounted;

    switch(state)
    {
    case MOUNTED:
        isMounted = true;
        break;

    case UNMOUNTED:
        isMounted = false;
        break;
    }

    Database::prepare("update guardian set mounted = :mounted, drive = :drive where  name = :guardianname");
    Database::bind("mounted", isMounted);
    Database::bind("drive", *(new QString(drive)));
    Database::bind("guardianname", *guardianName);
    Database::exec();
}

void DataManager::setItemProtected(QString path, bool value)
{
    Database::prepare("update item set protected = :protected where path = :path");
    Database::bind("protected", value);
    Database::bind("path", path);
    Database::exec();
}

QString *DataManager::getEncryptedKey(QString guardianName)
{
    QString *key = new QString;

    key = Database::selectString("code", "guardian", Database::where("name", guardianName));

    return key;
}

void DataManager::addGuardian(QString guardianName, QString encryptedText, char drive)
{
    QList<int> *guardianIds = new QList<int>;
    guardianIds = Database::selectIntegerList("id", "guardian");

    Database::prepare("insert into guardian values (:id, :name, :code, :mounted, :drive)");

    if(guardianIds->isEmpty())
    {
        Database::bind("id", 0);
    }
    else
    {
       Database::bind("id", guardianIds->last() + 1);
    }

    Database::bind("name", guardianName);
    Database::bind("code", encryptedText);
    Database::bind("mounted", true);
    Database::bind("drive", *(new QString(drive)));
    Database::exec();
}

void DataManager::deleteGuardian(QString guardianName)
{
    Database::prepare("delete from guardian where guardian = :guardian");
    Database::bind("name", guardianName);
    Database::exec();
}

void DataManager::deleteItem(QString itempath)
{
    Database::prepare("delete from item where path = :path");
    Database::bind("path", itempath);
    Database::exec();
}

void DataManager::deleteItems(QString guardianName)
{
    int guardianId = Database::selectInteger("id", "guardian", Database::where("name", guardianName));
    Database::exec("delete from item " + *(Database::where("guardian", guardianId)));
}

void DataManager::deleteSystemKey()
{
    Database::exec("delete from systemkey");
    Database::exec("insert into systemkey values (0, -1, 1, 0)");
}

void DataManager::addItem(QString itemName, QString itemPath, ITEM_TYPE category, ITEM_GUARDIAN_STATE state, bool protection, QString guardianName)
{
    int guardianId = Database::selectInteger("id", "guardian", Database::where("name", guardianName));

    Database::prepare("insert into item values (:name, :path, :type, :guardian, :unlocked, :protected)");

    Database::bind("name", itemName);
    Database::bind("path", itemPath);

    switch(category)
    {
    case ITEM_FILE:
        Database::bind("type", 0);
        break;
    case ITEM_FOLDER:
        Database::bind("type", 1);
        break;
    case ITEM_APP:
        Database::bind("type", 2);
        break;
    }

    Database::bind("guardian", guardianId);

    switch(state)
    {
    case LOCKED:
        Database::bind("unlocked", false);
        break;
    case UNLOCKED:
        Database::bind("unlocked", true);
        break;
    }

    Database::bind("protected", protection);

    Database::exec();
}

void DataManager::createSystemKey(QString guardianName)
{
    int id = Database::selectInteger("id", "guardian", Database::where("name", guardianName));

    Database::prepare("update systemkey set created = 1, guardian = :guardianid, unlocked = 1, protected = 1");
    Database::bind("guardianid", id);
    Database::exec();
}

void DataManager::unmountAll()
{
    Database::exec("update guardian set mounted = 0, drive = '0'");
    DataManager::setItemsState(DataManager::getItems(), LOCKED);
}

bool DataManager::isGuardianMounted(QString guardianName)
{
    return Database::selectBoolean("mounted", "guardian", Database::where("name", guardianName));
}

bool DataManager::isPathReserved(QString itemPath)
{
    QString *testName = Database::selectString("name", "item", Database::where("path", itemPath));

    if(testName->isEmpty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DataManager::isSystemKey(QString guardianName)
{
    int id = Database::selectInteger("id", "systemkey");

    if(guardianName == Database::selectString("name", "guardian", Database::where("id", id)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DataManager::isSystemKeyMounted()
{
    return isGuardianMounted(*(Database::selectString("name", "guardian", Database::where("id", Database::selectInteger("guardian", "systemkey")))));
}

bool DataManager::isSystemProtected()
{
    return Database::selectBoolean("protected", "systemkey");
}

bool DataManager::isSystemUnlocked()
{
    return Database::selectBoolean("unlocked", "systemkey");
}

void DataManager::setSystemUnlocked(bool value)
{
    Database::prepare("update systemkey set unlocked = :unlocked");
    Database::bind("unlocked", value);
    Database::exec();
}

void DataManager::setSystemProtected(bool value)
{
    Database::prepare("update systemkey set protected = :protected");
    Database::bind("protected", value);
    Database::exec();
}

bool DataManager::isItemProtected(QString itemPath)
{
    return Database::selectBoolean("protected", "item", Database::where("path", itemPath));
}

void DataManager::connect(QString pathToDatabase)
{
    Database::connect(pathToDatabase);
}

void DataManager::disconnect()
{
    Database::disconnect();
}

bool DataManager::doesSystemKeyExist()
{
    return Database::selectBoolean("created", "systemkey");
}
