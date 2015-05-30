#include "fileFunctions.h"
#include "common/stringFunctions.h"

// Creates a file on a drive that holds a key and a decrypted message
// Mask: driveLetter://fileName
void writeToDrive(char driveLetter, char *fileName, char *name, char *key, char *inHex)
{
	wchar_t *lpath = createPath(driveLetter, fileName);

	HANDLE hFile = CreateFile(
        lpath,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
		);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

    char *buffer = createBuffer(name, key, inHex);

	DWORD dwBytesWrite;

	if (!WriteFile(
        hFile,
        buffer,
        strlen(buffer),
        &dwBytesWrite,
        (LPOVERLAPPED)NULL
		))
	{
		return;
	}


	CloseHandle(hFile);
}

// Scans a drive for a file
// Mask: driveLetter://#KEY#<key>#MESSAGE#<inHex>
bool extractInfo(char driveLetter, char *fileName, char *name, char *key, char *inHex)
{
    fillWithZeros(key, strlen(key));
    fillWithZeros(inHex, strlen(inHex));
    fillWithZeros(name, strlen(name));

    wchar_t *lpath = createPath(driveLetter, fileName);
    char *buffer = new char[SIZE_OF_READ_BUFFER];
    fillWithZeros(buffer, SIZE_OF_READ_BUFFER);

    DWORD dwBytesRead;

    HANDLE hFile = CreateFile(
        lpath,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    if (hFile == INVALID_HANDLE_VALUE)
    {

        CloseHandle(hFile);
        return false;
    }
    else
    {
        if (ReadFile(
            hFile,
            buffer,
            SIZE_OF_READ_BUFFER,
            &dwBytesRead,
            (LPOVERLAPPED)NULL
            ) == false)
        {
            CloseHandle(hFile);
            return false;
        }
        else
        {
            CloseHandle(hFile);

            if (extractFromBuffer(buffer, name, key, inHex) == false)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

bool extractFromBuffer(char *buffer, char *name, char *key, char *inHex)
{
    // Mask: #NAME#<name>#KEY#<key>#MESSAGE#<inHex>

    char *start = strstr(buffer, "#NAME#");

    if(start == nullptr)
    {
        return false;
    }

    start += (sizeof("#NAME#") - 1) / sizeof(char);

    char *finish = strstr(buffer, "#KEY#");
    if (finish == nullptr)
    {
        return false;
    }

    int iter = 0;
    while (start != finish)
    {
        name[iter] = *start;
        iter++;
        start += sizeof(char);
    }

    start += (sizeof("#KEY#") - 1) / sizeof(char);

    finish = strstr(buffer, "#MESSAGE#");
    if (finish == nullptr)
    {
        return false;
    }

    iter = 0;
    while (start != finish)
    {
        key[iter] = *start;
        iter++;
        start += sizeof(char);
    }

    start += (sizeof("#MESSAGE#") - 1) / sizeof(char);

    iter = 0;
    while (*start != '\0')
    {
        inHex[iter] = *start;

        iter++;
        start += sizeof(char);
    }

	return true;
}

// Forms a wide characters path variable
wchar_t* createPath(char driveLetter, char *fileName)
{
	int pathLen = 1 + strlen(":\\") + strlen(fileName);
	char *path = new char[pathLen + 1];

	fillWithZeros(path, pathLen + 1);

	path[0] = driveLetter;
	strcat(path, ":\\");
	strcat(path, fileName);

	static wchar_t *lpath = new wchar_t[pathLen + 1];
	fillWithZeros(lpath, pathLen + 1);

	mbstowcs(lpath, path, pathLen);

    delete[] path;

	return lpath;
}

// Forms a buffer for further writing
char* createBuffer(char *name, char *key, char *inHex)
{
    char nameInput[] = "#NAME#";
	char keyInput[] = "#KEY#";
	char messageInput[] = "#MESSAGE#";

    int bufferSize = strlen(nameInput) + strlen(name) + strlen(keyInput) + strlen(key) +
                     strlen(messageInput) + strlen(inHex);

	char *buffer = new char[bufferSize];
	fillWithZeros(buffer, bufferSize);

    strcat(buffer, nameInput);
    strcat(buffer, name);
	strcat(buffer, keyInput);
	strcat(buffer, key);
	strcat(buffer, messageInput);
	strcat(buffer, inHex);

	return buffer;
}

void deleteFile(char driveLetter, char *fileName)
{
    char *path = new char[1 + strlen(":\\") + strlen(fileName)];

    fillWithZeros(path, strlen(path));

    path[0] = driveLetter;
    strcat(path, ":\\");
    strcat(path, fileName);

    wchar_t *lpath = new wchar_t[strlen(path)];
    fillWithZeros(lpath, wcslen(lpath));

    mbstowcs(lpath, path, strlen((path)));

    DeleteFile(lpath);
}
