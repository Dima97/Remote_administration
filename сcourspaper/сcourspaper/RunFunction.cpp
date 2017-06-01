#include "Header.h"
#include <string>
#include <list>
#include <sstream>
void RebootPC()
{
	WinExec("shutdown -r -t 0", SW_HIDE);
	exit(0);
}
void ShutDownPC()
{
	WinExec("shutdown -s -t 0", SW_HIDE);
	exit(0);
}
void ExitSystemePC()
{
	WinExec("shutdown -l ", SW_HIDE);
	exit(0);
}
void OpenCD_ROM()
{
	mciSendString(_T("Set cdaudio door open wait"), NULL, 0, NULL);
}
void ShowFiles(struct Data *data)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile("D:\\RemoteAdministration\\*", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			send(data->Server,FindFileData.cFileName, 100, 0);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	send(data->Server, "0", 100, 0);
}
void CreatFile(char path[],struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char str[100] = "D:\\RemoteAdministration\\";
	strcat(str, path);
	printf("file created %s", str);
	if (CreateFile(LPCTSTR(str), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL) == INVALID_HANDLE_VALUE)
	{
		send(data->Server, "error, file wasn't created", 100, 0);
		printf("error, file wasn't created");
	}
	else {
		send(data->Server, "file was created", 100, 0);
		printf("file created %s", str);
	}
}
void DelFile(char path[],struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char str[100] = "D:\\RemoteAdministration\\";
	strcat(str, path);
	if (DeleteFile(LPCTSTR(str)) == 0)
	{
		send(data->Server,"error, file wasn't deleted",100,0);
		printf("error, file wasn't deleted");
	}
	else {
		send(data->Server, "file was deleted", 100, 0);
		printf("file deleteted %s", str);
	}
}
void WorkWithCursor(struct Data *data)
{
	while (1) {
		if (recv(data->Server, data->Massage, 200, 0) != SOCKET_ERROR)
		{ 
			int pos[2];
			pos[0] = 0;
			pos[1] = 0;
			char executValue = data->Massage[0];
			for (int i = 0; i < strlen(data->Massage); i++)
			{
				data->Massage[i] = data->Massage[i + 1];
			}
			char *ph = strtok(data->Massage, " ,");
			int i = 0;
			while(ph != NULL)
			{
				pos[i] = atoi(ph);
				ph = strtok(NULL, " ,");
				i++;
			}
			pos[0] = pos[0] * 17.2;
			pos[1] = pos[1] *  20.5;
			INPUT inp[3];
			memset(inp, 0, sizeof(inp));
			switch (executValue) {
			case 'M': {
				SetCursorPos(pos[0], pos[1]);
				break;
			}
			case 'C': {
				
				SetCursorPos(pos[0], pos[1]);
				printf("%d,%d\n", pos[0], pos[1]);
				inp[0].type = INPUT_MOUSE;
				inp[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // нажатие левой кнопки 

				inp[1].type = INPUT_MOUSE;
				inp[1].mi.dwFlags = MOUSEEVENTF_LEFTUP; // отпускание левой кнопки 
				SendInput(2, inp, sizeof(INPUT));
				
				break;
			}
			case 'D':
			{
				SetCursorPos(pos[0], pos[1]);
				inp[0].type = INPUT_MOUSE;
				inp[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; 

				inp[1].type = INPUT_MOUSE;
				inp[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(2, inp, sizeof(INPUT));
				SendInput(2, inp, sizeof(INPUT));
				break;
			}
			case 'W':
			{
				return;
			}
			}
		}
	}
		   
}
bool sendData(struct Data *data, void *buf, int bufLen)
{
	const char *pbuf = (const char *)buf;
	while (bufLen > 0)
	{
		int num = send(data->Server, pbuf, bufLen, 0);
		if (num == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				continue;
			}
			return false;
		}
		pbuf += num;
		bufLen -= num;
	}
	return true;
}
bool sendLong(struct Data *data, long value)
{
	value = htonl(value);
	return sendData(data, &value, sizeof(value));
}
bool sendFile(struct Data *data, FILE *f)
{
	fseek(f, 0, SEEK_END);
	long filesize = ftell(f);
	rewind(f);
	if (filesize == EOF)
		return false;
	if (!sendLong(data, filesize))
		return false;
	if (filesize > 0)
	{
		char buffer[1000000];
		do
		{
			size_t num = min(filesize, sizeof(buffer));
			num = fread(buffer, 1, num, f);
			if (num < 1)
				return false;
			if (!sendData(data, buffer, num))
				return false;
			filesize -= num;
		} while (filesize > 0);
	}
	return true;
}
void sendFileFunction(char path[],struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char str[100] = "D:\\RemoteAdministration\\";
	strcat(str, path);
	FILE *filehandle = fopen(str, "rb");
	if (filehandle != NULL)
	{
		printf("sent!");
		sendFile(data, filehandle);
		fclose(filehandle);
	}
	else printf("error");
}
void Execute(char path[])
{
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char str[100] = "D:\\RemoteAdministration\\";
	strcat(str, path);
	ShellExecute(NULL, "open", str, NULL, str, SW_SHOWNORMAL);
	return;
}
void CloseProgramm(char name[])
{
	setlocale(LC_CTYPE, "russian");
	for (int i = 0; i < strlen(name); i++)
	{
		name[i] = name[i + 1];
	}
	HWND hwnd;
	char p[100];
	hwnd = GetDesktopWindow();
	hwnd = GetWindow(hwnd, GW_CHILD);
	while (hwnd != 0)
	{
		hwnd = GetWindow(hwnd, GW_HWNDNEXT);
		if (IsWindowVisible(hwnd) && GetWindowText(hwnd, p, 100))
			if (strstr(p, name)) {
				printf("programm closed");
				PostMessage(FindWindow(NULL,p), WM_QUIT, 0, 0);
			}
	}
}
void GetInfoAboutWindows(struct Data *data) {
	HWND hwnd;
	char p[100];
	hwnd = GetDesktopWindow();
	hwnd = GetWindow(hwnd, GW_CHILD);
	while (hwnd != 0)
	{
		hwnd = GetWindow(hwnd, GW_HWNDNEXT);
		if (IsWindowVisible(hwnd) && GetWindowText(hwnd, p, 100))
			send(data->Server, p, 100, 0); 
	}
}
void CPY(char path[])
{
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char temp[100];
	strcpy(temp, path);
	char *ph = strtok(temp, "\\");
	char name[40];
	while (ph != NULL)
	{
		strcpy(name, ph);
		ph = strtok(NULL, "\\");
	}
	strcpy(temp,"D:\\RemoteAdministration\\");
	strcat(temp, name);
	CopyFile(path,temp, false);
	free(ph);
}