#include <cstdlib>
#include <cstring>
#include <ctime>
#include <random>
using namespace std;

// Generate string randomly
void getRandomString(char *string, const int length);

// Fills a string with zero symbols
void fillWithZeros(char *string, int length);

// Fills a string with zero symbols
void fillWithZeros(wchar_t *string, int length);

//Function to convert unsigned char to string of length 2
void Char2Hex(unsigned char ch, char* szHex);

//Function to convert string of length 2 to unsigned char
void Hex2Char(char const* szHex, unsigned char& rch);

//Function to convert string of unsigned chars to string of chars
void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);

//Function to convert string of chars to string of unsigned chars
void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
