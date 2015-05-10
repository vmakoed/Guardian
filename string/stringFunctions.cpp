#include "stringFunctions.h"

// Generate string randomly
void getRandomString(char *string, const int length)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	random_device rd;

	for (int i = 0; i < length; ++i)
	{
		string[i] = alphanum[rd() % (sizeof(alphanum) - 1)];
	}

	string[length] = 0;
}

// Fills a string with zero symbols
void fillWithZeros(char *string, int length)
{
	for (int i = 0; i < length; i++)
	{
		string[i] = '\0';
	}
}

// Fills a string with zero symbols
void fillWithZeros(wchar_t *string, int length)
{
    for (int i = 0; i < length; i++)
    {
        string[i] = '\0';
    }
}


//Function to convert unsigned char to string of length 2
void Char2Hex(unsigned char ch, char* szHex)
{
	unsigned char byte[2];
	byte[0] = ch / 16;
	byte[1] = ch % 16;
	for (int i = 0; i<2; i++)
	{
		if (byte[i] >= 0 && byte[i] <= 9)
			szHex[i] = '0' + byte[i];
		else
			szHex[i] = 'A' + byte[i] - 10;
	}
	szHex[2] = 0;
}

//Function to convert string of length 2 to unsigned char
void Hex2Char(char const* szHex, unsigned char& rch)
{
	rch = 0;
	for (int i = 0; i<2; i++)
	{
		if (*(szHex + i) >= '0' && *(szHex + i) <= '9')
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if (*(szHex + i) >= 'A' && *(szHex + i) <= 'F')
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}

//Function to convert string of unsigned chars to string of chars
void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize)
{
	int i;
	char szHex[3];
	pszHexStr[0] = 0;
	for (i = 0; i<iSize; i++)
	{
		Char2Hex(pucCharStr[i], szHex);
		strcat(pszHexStr, szHex);
	}
}

//Function to convert string of chars to string of unsigned chars
void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize)
{
	int i;
	unsigned char ch;
	for (i = 0; i<iSize; i++)
	{
		Hex2Char(pszHexStr + 2 * i, ch);
		pucCharStr[i] = ch;
	}
}
