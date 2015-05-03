#include "guardian.h"

Guardian::Guardian(int id, QString name)
{
    this->id = id;
    this->name = name;
}

QString Guardian::getName()
{
    return this->name;
}

void Guardian::setName(QString name)
{
    this->name = name;
}

int Guardian::getId()
{
    return this->id;
}


void Guardian::setId(int id)
{
    this->id = id;
}
