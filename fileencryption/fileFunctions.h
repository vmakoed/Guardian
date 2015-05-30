#include "windows.h"
#include <iostream>
using namespace std;

#define SIZE_OF_READ_BUFFER 128

// Creates a file on a drive that holds a key and a decrypted message
void writeToDrive(char driveLetter, char *fileName, char *name, char *key, char *inHex);

// Forms a wide characters path variable
wchar_t* createPath(char driveLetter, char *fileName);

// Forms a buffer for further writing
char* createBuffer(char *name, char *key, char *inHex);

// Scans a drive for a file
// Mask: driveLetter://#KEY#<key>#MESSAGE#<inHex>
bool extractInfo(char driveLetter, char *fileName, char *name, char *key, char *inHex);

bool extractFromBuffer(char *buffer, char *name, char *key, char *inHex);

void deleteFile(char driveLetter, char *fileName);
