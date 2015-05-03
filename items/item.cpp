#include "item.h"

Item::Item(QString name, QString path, ITEM_TYPE type, Guardian *guardian)
{
    this->name = name;
    this->path = path;
    this->type = type;
    this->guardian = guardian;
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

Guardian* Item::getGuardian()
{
    return this->guardian;
}


void Item::setGuardian(Guardian *guardian)
{
    this->guardian = guardian;
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






