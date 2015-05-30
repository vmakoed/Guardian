#include "Rijndael.h"
#include "fileencryption/cryptobject.h"
#include "common/stringFunctions.h"

#define KEY_LENGTH		16
#define BLOCK_SIZE		16

// Generates a structure object that holds an encrypted message, a decrypted message and a key
void generateCryptObject(struct CryptObject *generatedObject);

// Encrypts data with key and stores result in dest
void encrypt(char *key, char *data, char *dest);

// Decrypts data with key and stores result in dest
void decrypt(char *key, char *data, char *dest);

// Ensures if dataOut is the result if dataIn encryption with key
bool cryptTest(char *encryptedHex, char *key, char *decryptedHex);
