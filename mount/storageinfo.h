#ifndef STORAGEINFO
#define STORAGEINFO

#define MAX_NUM_OF_STORAGES	20
#define MAX_SIZE_OF_SYMBOLICLINKNAME 128
#define MAX_SIZE_OF_UNIQUEID 128
#define MAX_SIZE_OF_DEVICE_NAME 50

// Holds a symbolic link name and an unique ID of a storage
struct StorageInfo
{
    char szSymbolicLinkName[MAX_SIZE_OF_SYMBOLICLINKNAME];
    char szUniqueId[MAX_SIZE_OF_UNIQUEID];
};

// Holds an array of storageInfo objects and their capacity
struct StoragesInfo
{
    StorageInfo storages[MAX_NUM_OF_STORAGES];
    int lastStorageIndex;
};

// Holds drive letters and product names of USB storages and their capacity
struct USBInfo
{
    char driveLetters[MAX_NUM_OF_STORAGES];
    char productNames[MAX_NUM_OF_STORAGES][MAX_SIZE_OF_DEVICE_NAME];
    int storagesCapacity;
};

#endif // STORAGEINFO

