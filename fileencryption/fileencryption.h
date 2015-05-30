#ifndef FILEENCRYPTION_H
#define FILEENCRYPTION_H

#include "fileencryption/filemanager.h"
#include "fileencryption/encryptmanager.h"

#include <QString>

class FileEncryption
{

public:

    static QString* defineGuardian(char driveLetter);

    static void newCryptObject(CryptObject *cryptObject);
    static void writeCryptInfo(char drive, QString name, char *key, char *decrypted);
    static void deleteCryptInfo(char drive);
    static bool authentificate(char drive, QString encryptedText);
};

#endif // FILEENCRYPTION_H
