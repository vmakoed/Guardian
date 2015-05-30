#include "item.h"

Item::Item()
{

}

Item::Item(QString name, QString path, ITEM_TYPE type, ITEM_GUARDIAN_STATE state, bool isProtected, QString guardianName)
{
    this->name = name;
    this->path = path;
    this->type = type;
    this->state = state;
    this->guardianName = guardianName;
    this->isProtected = isProtected;
}

Item::~Item()
{

}

QString Item::getName()
{
    return this->name;
}

void Item::setName(QString name)
{
    this->name = name;
}

ITEM_GUARDIAN_STATE Item::getItemGuardianState()
{
    return this->state;
}


void Item::setItemGuardianState(ITEM_GUARDIAN_STATE state)
{
    this->state = state;
}

QString Item::getPath()
{
    return this->path;
}

void Item::setPath(QString path)
{
    this->path = path;
}

ITEM_TYPE Item::getType()
{
    return this->type;
}

void Item::setType(ITEM_TYPE type)
{
    this->type = type;
}

QString Item::getGuardianName()
{
    return guardianName;
}

void Item::setGuardianName(QString &value)
{
    guardianName = value;
}

bool Item::getIsProtected()
{
    return isProtected;
}

void Item::setIsProtected(bool value)
{
    isProtected = value;
}
