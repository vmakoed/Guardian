#include "encryptFunctions.h"

// Randomly generates a structure object that holds an encrypted message, a decrypted message and a key
void generateCryptObject(struct CryptObject *generatedObject)
{
	char *input = new char[BLOCK_SIZE + 1];
	getRandomString(input, BLOCK_SIZE);

	CharStr2HexStr((unsigned char*)input, generatedObject->inHex, BLOCK_SIZE);
	
	getRandomString(generatedObject->key, BLOCK_SIZE);

	char *encryptedData = new char[BLOCK_SIZE + 1];
	encrypt(generatedObject->key, input, encryptedData);

	CharStr2HexStr((unsigned char*)encryptedData, generatedObject->outHex, BLOCK_SIZE);
}

// Ensures if dataOut is the result if dataIn encryption with key
bool cryptTest(char *encryptedHex, char *key, char *decryptedHex)
{
	char *encryptedChar = new char[BLOCK_SIZE + 1];
	fillWithZeros(encryptedChar, BLOCK_SIZE + 1);

	HexStr2CharStr(encryptedHex, (unsigned char*)encryptedChar, BLOCK_SIZE);

	char *decryptedData = new char[BLOCK_SIZE + 1];
	decrypt(key, encryptedChar, decryptedData);

	char szHex[BLOCK_SIZE * 2 + 1];

	CharStr2HexStr((unsigned char*)decryptedData, szHex, BLOCK_SIZE);
	
	if (strcmp(decryptedHex, szHex) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Encrypts data with key and stores result in dest
void encrypt(char *key, char *data, char *dest)
{
	char *chain = new char[KEY_LENGTH];

	fillWithZeros(chain, KEY_LENGTH);

	CRijndael oRijndael;
	oRijndael.MakeKey(key, chain, KEY_LENGTH, BLOCK_SIZE);
	
	fillWithZeros(dest, BLOCK_SIZE);

	oRijndael.EncryptBlock(data, dest);
}

// Decrypts data with key and stores result in dest
void decrypt(char *key, char *data, char *dest)
{
	char *chain = new char[KEY_LENGTH];

	fillWithZeros(chain, KEY_LENGTH);

	CRijndael oRijndael;
	oRijndael.MakeKey(key, chain, KEY_LENGTH, BLOCK_SIZE);

	fillWithZeros(dest, BLOCK_SIZE);

	oRijndael.DecryptBlock(data, dest);
}