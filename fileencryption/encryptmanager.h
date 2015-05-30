#ifndef ENCRYPTMANAGER_H
#define ENCRYPTMANAGER_H

#include "Rijndael.h"
#include "fileencryption/cryptobject.h"
#include "common/stringFunctions.h"

#define KEY_LENGTH		32
#define BLOCK_SIZE		16

class EncryptManager
{
public:
    static void generateCryptObject(struct CryptObject *generatedObject);
    static void encrypt(char *key, char *data, char *dest);
    static void decrypt(char *key, char *data, char *dest);
    static bool cryptTest(char *encryptedHex, char *key, char *decryptedHex);
};

#endif // ENCRYPTMANAGER_H
