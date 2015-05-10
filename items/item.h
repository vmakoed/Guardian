#ifndef ITEM_H
#define ITEM_H

#include <QString>

#include "guardians/guardian.h"

typedef enum {ITEM_FILE = 1, ITEM_FOLDER = 2, ITEM_APP = 3} ITEM_TYPE;

class Item
{
private:
    QString name;
    QString path;
    ITEM_TYPE type;
    Guardian *guardian;

public:
    Item(QString name, QString path, ITEM_TYPE type, Guardian *guardian);
    ~Item();

    QString getName();
    void setName(QString name);
    QString getPath();
    void setPath(QString path);
    ITEM_TYPE getType();
    void setType(ITEM_TYPE type);
    Guardian* getGuardian();
    void setGuardian(Guardian *guardian);
};

#endif // ITEM_H
