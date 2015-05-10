#ifndef GUARDIANSMODEL_H
#define GUARDIANSMODEL_H

#include <QObject>

#include "guardians/guardian.h"
#include "crypto/encryptFunctions.h"
#include "mount/getStoragesInfo.h"

class GuardiansModel : public QObject
{
    Q_OBJECT

public:
    GuardiansModel(QObject *parent = 0);
    QList<Guardian*>* guardians();
    void scanDrives();
    void addGuardian(QString drive, QString name);
    void writeInfoToDatabase(QString name, char* outHex);
    bool checkGuardian(QString name, char *key, char *inHex);
    void getCodeFromDatabase(QString name, char *code);
    void mount(char *name);
    void unmountAll();
};

#endif // GUARDIANSMODEL_H
