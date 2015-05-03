#ifndef GUARDIAN_H
#define GUARDIAN_H

#include <QString>

class Guardian
{
private:
    int id;
    QString name;

public:
    Guardian(int id, QString name);
    ~Guardian();

    int getId();
    void setId(int id);
    QString getName();
    void setName(QString name);
};

#endif // GUARDIAN_H
