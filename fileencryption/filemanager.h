#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "common/stringFunctions.h"
#include "Windows.h"

#define SIZE_OF_READ_BUFFER 128

class FileManager
{
public:
    static void writeToDrive(char driveLetter, char *fileName, char *name, char *key, char *inHex);
    static wchar_t* createPath(char driveLetter, char *fileName);
    static char* createBuffer(char *name, char *key, char *inHex);
    static bool extractInfo(char driveLetter, char *fileName, char *name, char *key, char *inHex);
    static bool extractFromBuffer(char *buffer, char *name, char *key, char *inHex);
    static void deleteFile(char driveLetter, char *fileName);
};

#endif // FILEMANAGER_H
