#include "guardian.h"

Guardian::Guardian(QString name)
{
    this->name = name;
    this->state = UNMOUNTED;
}

QString Guardian::getName()
{
    return this->name;
}

void Guardian::setName(QString name)
{
    this->name = name;
}

STORAGE_STATE Guardian::getState()
{
    return state;
}

void Guardian::setState(STORAGE_STATE state)
{
    this->state = state;
}
