#ifndef GUARDIAN_H
#define GUARDIAN_H

#include <QString>

typedef enum { UNMOUNTED = 0, MOUNTED = 1 } GUARDIAN_STATE;

class Guardian
{
private:
    QString name;
    GUARDIAN_STATE state;
    char drive;

public:
    Guardian();
    Guardian(QString name, GUARDIAN_STATE state, char drive);
    ~Guardian();

    char getDrive();
    void setDrive(char drive);
    QString getName();
    void setName(QString name);
    GUARDIAN_STATE getState();
    void setState(GUARDIAN_STATE state);

};

#endif // GUARDIAN_H
