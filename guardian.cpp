#include "guardian.h"

Guardian::Guardian()
{

}

Guardian::Guardian(QString name, GUARDIAN_STATE state, char drive)
{
    this->name.clear();
    this->name.append(name);
    this->state = state;

    if(state == UNMOUNTED)
    {
        this->drive = '0';
    }
    else
    {
        this->drive = drive;
    }

}

char Guardian::getDrive()
{
    return this->drive;
}

void Guardian::setDrive(char drive)
{
    this->drive = drive;
}

QString Guardian::getName()
{
    return this->name;
}

void Guardian::setName(QString name)
{
    this->name.clear();
    this->name.append(name);
}

GUARDIAN_STATE Guardian::getState()
{
    return state;
}

void Guardian::setState(GUARDIAN_STATE state)
{
    this->state = state;
}
