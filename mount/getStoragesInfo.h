#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <wchar.h>

#include "storageinfo.h"

#include <C:\Program Files (x86)\Windows Kits\8.1\Include\km\mountmgr.h>
#pragma comment(lib, "Crypt32.lib")

// Returns an object of usbInfo structure that holds drive letters and product names of mounted USB storages
void getUSBInfo(struct USBInfo* dest);

// Returns an object of storagesInfo structure that holds symbolic links and unique IDs of mounted storage devices
void getStoragesInfo(struct StoragesInfo* dest);

// Returns an object of usbInfo that holds drive letters and product names converted from unique IDs and symbolic links
// of USB storages from srcStorageArray
void extractUSBStoragesInfo(struct USBInfo* dest, StoragesInfo *srcStoragesArray);

// Extracts drive letter from symbolicLinkName
char extractDriveLetter(char szSymbolicLinkName[]);

// Extracts device name from szUniqueId. Leaves only vendor and product names separated by a space.
void extractDeviceName(char *dest, char szUniqueId[]);
