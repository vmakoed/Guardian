#include "fileencryption.h"

QString* FileEncryption::defineGuardian(char driveLetter)
{
    char *name = new char[255];
    char *key = new char[KEY_LENGTH];
    char *inHex = new char[BLOCK_SIZE * 2 + 1];

    if(FileManager::extractInfo(driveLetter, "pass.guardian", name, key, inHex))
    {
        return (new QString(name));
    }
    else
    {
        return nullptr;
    }
}

void FileEncryption::newCryptObject(CryptObject *cryptObject)
{
    EncryptManager::generateCryptObject(cryptObject);
}

void FileEncryption::writeCryptInfo(char drive, QString name, char *key, char *decrypted)
{
    QByteArray array = name.toLocal8Bit();
    char* buffer = array.data();

    FileManager::writeToDrive(drive, "pass.guardian", buffer, key, decrypted);
}

void FileEncryption::deleteCryptInfo(char drive)
{
    FileManager::deleteFile(drive, "pass.guardian");
}

bool FileEncryption::authentificate(char drive, QString encryptedText)
{
    char *inHex = new char[BLOCK_SIZE * 2 + 1];
    char *key = new char[KEY_LENGTH];
    char *name = new char[255];

    FileManager::extractInfo(drive, "pass.guardian", name, key, inHex);

    QByteArray array = encryptedText.toLocal8Bit();
    char* buffer = array.data();

    if(EncryptManager::cryptTest(buffer, key, inHex))
    {
        return true;
    }
    else
    {
        return false;
    }
}

