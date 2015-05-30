#ifndef ITEMSLOCKER_H
#define ITEMSLOCKER_H

#include <QList>

#include "item.h"
#include "itemslocker/redefineAccess.h"

class ItemsLocker
{

public:
    static void alterAccess(QList<Item *> *items, ITEM_GUARDIAN_STATE state);
    static void alterAccess(Item *item, ITEM_GUARDIAN_STATE state);
};

#endif // ITEMSLOCKER_H
