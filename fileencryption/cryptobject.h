#ifndef CRYPTOBJECT
#define CRYPTOBJECT

#define KEY_LENGTH 32
#define BLOCK_SIZE 16

struct CryptObject
{
    char inHex[BLOCK_SIZE * 2 + 1];
    char key[KEY_LENGTH + 1];
    char outHex[BLOCK_SIZE * 2 + 1];
};

#endif // CRYPTOBJECT

