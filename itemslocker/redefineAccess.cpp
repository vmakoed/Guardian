#include "itemslocker/RedefineAccess.h"

DWORD RedefineAccess (wchar_t wchDirName[], wchar_t wchUserName[], AccessMode accessAceType, DWORD accessMask)
{
	PSECURITY_DESCRIPTOR lpSd = 0;	
	DWORD dwSdLength = 0;				

	PSID lpSid = 0;				
	DWORD dwSidLength = 0;			

	SECURITY_DESCRIPTOR sdAbsoluteSd; 
	ACL *lpNewDacl = 0;    

	DWORD dwRetCode;

	if (GetSD (wchDirName, lpSd, dwSdLength) != 0)
	{
		dwRetCode = GetLastError();

		printf("Getting SD failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

    if (GetWellKnownSID(WinWorldSid, lpSid, dwSidLength) != 0)
	{
		dwRetCode = GetLastError();

		printf ("Getting SID failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	if (AddACE (lpSd, dwSdLength, lpSid, dwSidLength, accessAceType, accessMask, lpNewDacl) != 0)
	{
		dwRetCode = GetLastError();

		printf ("Adding ACE failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}
	
	if (SetDACL (wchDirName, sdAbsoluteSd, lpNewDacl) != 0)
	{
		printf ("Setting DACL failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	delete[] lpSd;
	delete[] lpSid;
	delete[] lpNewDacl;

	return 0;
}



DWORD GetWellKnownSID (WELL_KNOWN_SID_TYPE sidType, PSID &lpSid, DWORD &dwSidLength)
{
	DWORD dwRetCode;

	if (CreateWellKnownSid (sidType, nullptr, nullptr, &dwSidLength) == 0)
	{
		dwRetCode = GetLastError();

		if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
		{
			lpSid = (SID*) new char[dwSidLength];
		}
		else
		{
			printf ("Sid creation failed.\n");
			printf ("Error code: %d\n", dwRetCode);

			return dwRetCode;
		}
	}

	if (CreateWellKnownSid (sidType, nullptr, lpSid, &dwSidLength) == 0)
	{
		dwRetCode = GetLastError();		
		printf ("Sid creation failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	return 0;
}



DWORD GetSD (wchar_t wchDirName[], PSECURITY_DESCRIPTOR &lpSd, DWORD &dwSdLength)
{
	DWORD dwRetCode; 

	if (GetFileSecurity (wchDirName, DACL_SECURITY_INFORMATION, lpSd, 0, &dwSdLength) == 0) 
	{
		dwRetCode = GetLastError();

		if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
		{
			lpSd = (SECURITY_DESCRIPTOR*) new char[dwSdLength];
		}
		else
		{
			printf ("Get file security failed.\n");
			printf ("Error code: %d\n", dwRetCode);

			return dwRetCode;
		}
	}

	if (GetFileSecurity (wchDirName, DACL_SECURITY_INFORMATION, lpSd, dwSdLength, &dwSdLength) == 0)
	{
		dwRetCode = GetLastError();
		printf ("Get file security failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	return 0;
}



DWORD GetSID (wchar_t wchUserName[], PSID &lpSid, DWORD &dwSidLength)
{
	DWORD dwLengthOfDomainName = 0;    
	LPTSTR lpDomainName = nullptr;
	SID_NAME_USE typeOfSid;

	DWORD dwRetCode; 

	if (LookupAccountName (0, wchUserName, 0, &dwSidLength, 0, &dwLengthOfDomainName, &typeOfSid) == 0)
	{
		dwRetCode = GetLastError();

		if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
		{
			// распределяем память для SID
			lpSid = (SID*) new char[dwSidLength];
			lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
		}
		else
		{
			printf ("Lookup account name failed.\n");
			printf ("Error code: %d\n", dwRetCode);

			return dwRetCode;
		}
	}

	if (LookupAccountName (0, wchUserName, lpSid, &dwSidLength, lpDomainName, &dwLengthOfDomainName, &typeOfSid) == 0)
	{
		dwRetCode = GetLastError();

		printf ("Lookup account name failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	delete[] lpDomainName;

	return 0;
}



DWORD AddACE (PSECURITY_DESCRIPTOR &lpSd, DWORD &dwSdLength, PSID &lpSid, DWORD &dwSidLength, bool accessAceType,
              DWORD accessMask, ACL *&lpNewDacl)
{
	DWORD dwRetCode;

	ACL *lpOldDacl;
	LPVOID lpAce; 

	DWORD dwDaclLength = 0;

	BOOL bDaclPresent;
	BOOL bDaclDefaulted;

	if (GetSecurityDescriptorDacl (lpSd, &bDaclPresent, &lpOldDacl, &bDaclDefaulted) == 0)
	{
		dwRetCode = GetLastError();
		printf ("Get security descriptor DACL failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	switch (accessAceType)
	{
	case ACCESS_ALLOWED:
		dwDaclLength = lpOldDacl->AclSize + sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + dwSidLength;
		break;

	case ACCESS_DENIED:
		dwDaclLength = lpOldDacl->AclSize + sizeof(ACCESS_DENIED_ACE) - sizeof(DWORD) + dwSidLength;
		break;
	}

	lpNewDacl = (ACL*) new char[dwDaclLength];

	if (InitializeAcl (lpNewDacl, dwDaclLength, ACL_REVISION) == 0) 
	{
		dwRetCode = GetLastError();

		printf ("Lookup account name failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	switch (accessAceType)
	{
	case ACCESS_ALLOWED:
		if (AddAccessAllowedAce (lpNewDacl, ACL_REVISION, accessMask, lpSid) == 0)
		{
			dwRetCode = GetLastError();
			perror ("Add access allowed ace failed.\n");
			printf ("The last error code: %u\n", dwRetCode);

			return dwRetCode;
		}

		break;

	case ACCESS_DENIED:
		if (AddAccessDeniedAce (lpNewDacl, ACL_REVISION, accessMask, lpSid) == 0)
		{
			dwRetCode = GetLastError();
			perror ("Add access allowed ace failed.\n");
			printf ("The last error code: %u\n", dwRetCode);

			return dwRetCode;
		}

		break;
	}

	if (GetAce (lpOldDacl, 0, &lpAce) == 0)
	{
		dwRetCode = GetLastError();

		printf ("Get ace failed.\n");
		printf ("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	if (bDaclPresent)
	{
		if (AddAce (lpNewDacl, ACL_REVISION, MAXDWORD, lpAce, lpOldDacl->AclSize - sizeof(ACL)) == 0)
		{
			dwRetCode = GetLastError();
			perror ("Add access allowed ace failed.\n");
			printf ("The last error code: %u\n", dwRetCode);

			return dwRetCode;
		}
	}

	if (IsValidAcl (lpNewDacl) == 0)
	{
		dwRetCode = GetLastError();
		perror ("The new ACL is invalid.\n");
		printf ("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	printf ("ACE added successfully\n");

	return 0;
}



DWORD SetDACL (wchar_t wchDirName[], SECURITY_DESCRIPTOR &sdAbsoluteSd, ACL *&lpNewDacl)
{
	DWORD dwRetCode;

	if (InitializeSecurityDescriptor (&sdAbsoluteSd, SECURITY_DESCRIPTOR_REVISION) == 0)
	{
		dwRetCode = GetLastError();
		perror("Initialize security descriptor failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	if (SetSecurityDescriptorDacl (&sdAbsoluteSd, TRUE, lpNewDacl, FALSE) == 0)
	{
		dwRetCode = GetLastError();
		perror("Set security descriptor DACL failed.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	if (IsValidSecurityDescriptor (&sdAbsoluteSd) == 0)
	{
		dwRetCode = GetLastError();
		perror("Security descriptor is invalid.\n");
		printf("The last error code: %u\n", dwRetCode);

		return dwRetCode;
	}

	if (SetFileSecurity (wchDirName, DACL_SECURITY_INFORMATION, &sdAbsoluteSd) == 0)
	{
		dwRetCode = GetLastError();
		printf("Set file security failed.\n");
		printf("Error code: %d\n", dwRetCode);

		return dwRetCode;
	}

	printf("DASL set successfully\n");

	return 0;
}
