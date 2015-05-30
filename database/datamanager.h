#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include "database/database.h"

#include "item.h"
#include "guardian.h"

class DataManager
{

public:
    static QList<Item*>* getItems();
    static QList<Item*>* getItems(ITEM_TYPE type);
    static QList<Item*>* getItems(QString guardianName);

    static QString *getSystemKeyName();
    static Item* getSystemItem();

    static QList<Guardian*>* getGuardians();
    static QList<Guardian*>* getGuardians(GUARDIAN_STATE state);

    static QString getGuardianCode(QString guardianName);

    static void setItemsState(QList<Item*> *items, ITEM_GUARDIAN_STATE state);
    static void setGuardianState(QString *guardianName, GUARDIAN_STATE state, char drive);

    static void setItemProtected(QString path, bool value);

    static QString* getEncryptedKey(QString guardianName);

    static void addGuardian(QString guardianName, QString encryptedText, char drive);
    static void addItem(QString itemName, QString itemPath, ITEM_TYPE type, ITEM_GUARDIAN_STATE state, bool protection, QString guardianName);
    static void createSystemKey(QString guardianName);

    static QString* getGuardianName(char drive);
    static GUARDIAN_STATE getGuardianState(QString guardianName);

    static void deleteGuardian(QString guardianName);
    static void deleteItem(QString itempath);
    static void deleteItems(QString guardianName);
    static void deleteSystemKey();

    static void unmountAll();

    static bool isGuardianMounted(QString guardianName);
    static bool isPathReserved(QString itemPath);
    static bool isNameReserved(QString guardianName);
    static bool isSystemKey(QString guardianName);
    static bool isItemProtected(QString itemPath);

    static void connect(QString pathToDatabase);
    static void disconnect();

    static bool doesSystemKeyExist();
    static bool isSystemProtected();
    static bool isSystemUnlocked();
    static bool isSystemKeyMounted();

    static void setSystemUnlocked(bool value);
    static void setSystemProtected(bool value);
};

#endif // DATAMANAGER_H
