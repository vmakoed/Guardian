#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <sddl.h>
#include <AclAPI.h>

#pragma comment(lib, "Advapi32.lib")

typedef enum { ACCESS_DENIED = 0, ACCESS_ALLOWED = 1 } AccessMode;

DWORD RedefineAccess(wchar_t wchDirName[], wchar_t wchUserName[], AccessMode accessAceType, DWORD accessMask);

DWORD GetSD (wchar_t wchDirName[], PSECURITY_DESCRIPTOR &lpSd, DWORD &dwSdLength);
DWORD GetSID (wchar_t wchUserName[], PSID &lpSid, DWORD &dwSidLength);
DWORD GetWellKnownSID (WELL_KNOWN_SID_TYPE sidType, PSID &lpSid, DWORD &dwSidLength);
DWORD AddACE (PSECURITY_DESCRIPTOR &lpSd, DWORD &dwSdLength, PSID &lpSid, DWORD &dwSidLength, bool accessAceType, 
			  DWORD accessMask, ACL *&lpNewDacl);
DWORD SetDACL (wchar_t wchDirName[], SECURITY_DESCRIPTOR &sdAbsoluteSd, ACL *&lpNewDacl); // установить новый Acess Control List
