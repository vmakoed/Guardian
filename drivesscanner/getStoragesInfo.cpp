#include "getStoragesInfo.h"

// Fills dest with drive letters and product names of mounted USB storages
void getUSBInfo(struct USBInfo* dest)
{
    struct StoragesInfo *storagesInfo = new StoragesInfo;
    storagesInfo->lastStorageIndex = 0;

    getStoragesInfo(storagesInfo);
    extractUSBStoragesInfo(dest, storagesInfo);

    delete[] storagesInfo;
}

// Fills dest symbolic links and unique IDs of mounted storage devices
void getStoragesInfo(struct StoragesInfo* storagesInfo)
{
    HANDLE hMountMgr;

    // MOUNTMGR_DOS_DEVICE_NAME is defined as L"\\\\.\\MountPointManager"
    hMountMgr = CreateFile(
        MOUNTMGR_DOS_DEVICE_NAME,
        0,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING,
        0,
        NULL);

    if (hMountMgr == INVALID_HANDLE_VALUE)
    {
        return;
    }

    DWORD cbBytesReturned;
    LPTSTR pszLogicalDrives;

    cbBytesReturned = GetLogicalDriveStrings(0, NULL);
    pszLogicalDrives = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, cbBytesReturned * sizeof(TCHAR));

    cbBytesReturned = GetLogicalDriveStrings(cbBytesReturned, pszLogicalDrives);

    for (LPTSTR pszDriveRoot = pszLogicalDrives; *pszDriveRoot != TEXT('\0'); pszDriveRoot += lstrlen(pszDriveRoot) + 1)
    {
        wchar_t szDeviceName[7] = (L"\\\\.\\");
        szDeviceName[4] = pszDriveRoot[0];
        szDeviceName[5] = _T(':');
        szDeviceName[6] = _T('\0');

        HANDLE hDevice = CreateFile(
            szDeviceName,
            0,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );

        if (hDevice == INVALID_HANDLE_VALUE)
        {
            return;
        }

        BYTE byBuffer[1024];

        BOOL bSuccess = DeviceIoControl(
            hDevice,
            IOCTL_MOUNTDEV_QUERY_DEVICE_NAME,
            NULL,
            0,
            (LPVOID)byBuffer,
            sizeof(byBuffer),
            &cbBytesReturned, (LPOVERLAPPED)NULL
        );

        PMOUNTDEV_NAME pMountDevName = (PMOUNTDEV_NAME)byBuffer;
        bSuccess = CloseHandle(hDevice);

        DWORD dwInBuffer = pMountDevName->NameLength + sizeof(MOUNTMGR_MOUNT_POINT);
        PBYTE pbyInBuffer = (PBYTE)LocalAlloc(LMEM_ZEROINIT, dwInBuffer);

        PMOUNTMGR_MOUNT_POINT pMountPoint = (PMOUNTMGR_MOUNT_POINT)pbyInBuffer;
        pMountPoint->DeviceNameLength = pMountDevName->NameLength;
        pMountPoint->DeviceNameOffset = sizeof(MOUNTMGR_MOUNT_POINT);

        CopyMemory(pbyInBuffer + sizeof(MOUNTMGR_MOUNT_POINT), pMountDevName->Name, pMountDevName->NameLength);

        DWORD dwOutBuffer = 1024 + sizeof(MOUNTMGR_MOUNT_POINTS);
        PBYTE pbyOutBuffer = (PBYTE)LocalAlloc(LMEM_ZEROINIT, dwOutBuffer);

        bSuccess = DeviceIoControl(hMountMgr,
            IOCTL_MOUNTMGR_QUERY_POINTS, pbyInBuffer, dwInBuffer, (LPVOID)pbyOutBuffer,
            dwOutBuffer, &cbBytesReturned, (LPOVERLAPPED)NULL);

        DWORD ccb;

        if (bSuccess)
        {
            PMOUNTMGR_MOUNT_POINTS pMountPoints = (PMOUNTMGR_MOUNT_POINTS)pbyOutBuffer;

            for (int i = 0; i < pMountPoints->NumberOfMountPoints; i++)
            {
                TCHAR szUniqueId[MAX_SIZE_OF_UNIQUEID];
                TCHAR szSymbolicLinkName[MAX_SIZE_OF_SYMBOLICLINKNAME];

                ccb = sizeof(szUniqueId) / sizeof(szUniqueId[0]);

                if (CryptBinaryToString(
                    pbyOutBuffer + pMountPoints->MountPoints[i].UniqueIdOffset,
                    pMountPoints->MountPoints[i].UniqueIdLength,
                    CRYPT_STRING_BASE64,
                    szUniqueId,
                    &ccb
                ) == 0)
                {
                    swprintf(
                        szUniqueId,
                        pMountPoints->MountPoints[i].UniqueIdLength / sizeof(WCHAR),
                        L"%ls",
                        pbyOutBuffer + pMountPoints->MountPoints[i].UniqueIdOffset
                    );

                    swprintf(
                        szSymbolicLinkName,
                        pMountPoints->MountPoints[i].SymbolicLinkNameLength / sizeof(WCHAR),
                        L"%ls\n",
                        pbyOutBuffer + pMountPoints->MountPoints[i].SymbolicLinkNameOffset
                    );

                    wcstombs(
                        storagesInfo->storages[storagesInfo->lastStorageIndex].szUniqueId,
                        szUniqueId,
                        sizeof(storagesInfo->storages[storagesInfo->lastStorageIndex].szUniqueId)
                    );

                    wcstombs(
                        storagesInfo->storages[storagesInfo->lastStorageIndex].szSymbolicLinkName,
                        szSymbolicLinkName,
                        sizeof(storagesInfo->storages[storagesInfo->lastStorageIndex].szSymbolicLinkName)
                    );

                    storagesInfo->lastStorageIndex++;
                }

            }
        }

        pbyInBuffer = (PBYTE)LocalFree(pbyInBuffer);
        pbyOutBuffer = (PBYTE)LocalFree(pbyOutBuffer);
    }

    pszLogicalDrives = (LPTSTR)LocalFree(pszLogicalDrives);
    CloseHandle(hMountMgr);
}

// Fills dest with letters and product names converted from unique IDs and symbolic links
// of USB storages from srcStoragesInfo
void extractUSBStoragesInfo(struct USBInfo* dest, StoragesInfo *srcStoragesInfo)
{
    dest->storagesCapacity = 0;

    for (int i = 0; i < srcStoragesInfo->lastStorageIndex; i++)
    {
        if (strstr(srcStoragesInfo->storages[i].szUniqueId, "USBSTOR"))
        {
            if (strstr(srcStoragesInfo->storages[i].szSymbolicLinkName, "DosDevices"))
            {
                extractDeviceName(dest->productNames[dest->storagesCapacity], srcStoragesInfo->storages[i].szUniqueId);

                dest->driveLetters[dest->storagesCapacity] =
                    extractDriveLetter(srcStoragesInfo->storages[i].szSymbolicLinkName);

                dest->storagesCapacity++;
            }
        }
    }

    dest->driveLetters[dest->storagesCapacity] = '\0';
}

// Extracts drive letter from symbolicLinkName
char extractDriveLetter(char szSymbolicLinkName[])
{
    // Mask: /DosDevices/? (? is the 12th char)
    return szSymbolicLinkName[12];
}

// Extracts device name from szUniqueId into dest. Leaves only vendor and product names separated by a space.
void extractDeviceName(char *dest, char szUniqueId[])
{
    char *start = strstr(szUniqueId, "#Disk&Ven_");

    start += (sizeof("#Disk&Ven_") - 1) / sizeof(char);

    char *finish = strstr(szUniqueId, "&Prod_");

    int iter = 0;
    while (start != finish)
    {
        dest[iter] = *start;
        iter++;
        start += sizeof(char);
    }

    dest[iter] = ' ';
    iter++;

    start += (sizeof("&Prod_") - 1) / sizeof(char);
    finish = strstr(szUniqueId, "&Rev_");
    while (start != finish)
    {
        if (*start == '_')
        {
            dest[iter] = ' ';
        }
        else
        {
            dest[iter] = *start;
        }

        iter++;
        start += sizeof(char);
    }

    dest[iter] = '\0';
}
