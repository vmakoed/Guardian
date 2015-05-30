#include "itemslocker/itemslocker.h"

void ItemsLocker::alterAccess(QList<Item *> *items, ITEM_GUARDIAN_STATE state)
{
    for(auto item : *items)
    {
        alterAccess(item, state);
    }
}

void ItemsLocker::alterAccess(Item *item, ITEM_GUARDIAN_STATE state)
{
    wchar_t *path = new wchar_t[255];
    item->getPath().toWCharArray(path);
    path[item->getPath().size()] = L'\0';

    switch(state)
    {
    case UNLOCKED:
        RedefineAccess(path, L"Victor Makoed", ACCESS_ALLOWED, GENERIC_ALL);
        break;
    case LOCKED:
        RedefineAccess(path, L"Victor Makoed", ACCESS_DENIED, GENERIC_ALL);
        break;
    }
}

