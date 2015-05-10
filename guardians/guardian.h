#ifndef GUARDIAN_H
#define GUARDIAN_H

#include <QString>

typedef enum { MOUNTED, UNMOUNTED } STORAGE_STATE;

class Guardian
{
private:
    int id;
    QString name;
    STORAGE_STATE state;

public:
    Guardian(QString name);
    ~Guardian();

    QString getName();
    void setName(QString name);
    STORAGE_STATE getState();
    void setState(STORAGE_STATE state);

};

#endif // GUARDIAN_H
