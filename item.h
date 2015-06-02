#ifndef ITEM_H
#define ITEM_H

#include <QString>

typedef enum {ITEM_FILE, ITEM_FOLDER, ITEM_SYSTEM} ITEM_TYPE;
typedef enum {LOCKED, UNLOCKED} ITEM_GUARDIAN_STATE;

class Item
{
private:
    QString name;
    QString path;
    ITEM_TYPE type;
    ITEM_GUARDIAN_STATE state;
    bool isProtected;

    QString guardianName;

public:
    Item();
    Item(QString name, QString path, ITEM_TYPE type, ITEM_GUARDIAN_STATE state, bool isProtected, QString guardianName);
    ~Item();

    QString getName();
    void setName(QString name);
    QString getPath();
    void setPath(QString path);
    ITEM_TYPE getType();
    void setType(ITEM_TYPE type);
    ITEM_GUARDIAN_STATE getItemGuardianState();
    void setItemGuardianState(ITEM_GUARDIAN_STATE state);
    QString getGuardianName();
    void setGuardianName(QString &value);
    bool getIsProtected();
    void setIsProtected(bool value);
};

#endif // ITEM_H
