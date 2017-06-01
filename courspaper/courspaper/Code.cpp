#include "Header.h"
void funHelp() {
	printf("mkfile - make file in folder RemoteAdministration\n");
	printf("delfile - delete file from folder RemoteAdministration\n");
	printf("execpr - run programm in remote PC\n");
	printf("closepr - close runing programm in remote PC\n");
	printf("getfile - download file from remote PC from RemoteAdministration's folder\n");
	printf("getcursor - run cursor in remote PC\n");
	printf("getsystinfo - getinng information about remote PC\n");
	printf("getinfotasks - geting information about active window in remote PC\n");
	printf("reboot - rebooting PC\n");
	printf("exitsyst - exit from systeme\n");
	printf("opencd - open CD-ROM in remote PC\n");
	printf("exit - close the programm\n");
	printf("help - geting information about function\n");
	printf("copyinfold - copying files in folder RemoteAdministration\n");
	printf("showfile - show file from folder RemoteAdministration\n");
	printf("connect - connecting with remote PC if connecting was ended\n");
	printf("cls - clear console\n");
 }
bool readdata(struct Data *data, void *buf, int buflen)
{
	char *pbuf = (char *)buf;

	while (buflen > 0)
	{
		int num = recv(data->Sock, pbuf, buflen, 0); 
		if (num == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				continue;
			}
			return false;
		}
		else if (num == 0)
			return false;

		pbuf += num;
		buflen -= num;
	}

	return true;
}

bool readlong(struct Data *data, long *value)
{
	if (!readdata(data, value, sizeof(value)))
		return false;
	*value = ntohl(*value);
	return true;
}

bool readfile(struct Data *data, FILE *f)
{
	long filesize;
	if (!readlong(data, &filesize))
		return false;
	if (filesize > 0)
	{
		if (data->procent == 0)
			data->procent = filesize;
		char buffer[1000000];
		do
		{
			int num = min(filesize, sizeof(buffer));
			if (!readdata(data, buffer, num))
				return false;
			int offset = 0;
			do
			{
				size_t written = fwrite(&buffer[offset], 1, num - offset, f);
				if (written < 1)
					return false;
				offset += written;
			} while (offset < num);
			filesize -= num;
			double b =(double) (data->procent - filesize) / data->procent;
			int c = b * 100;
			printf("downloading: %d%%\r", c);
			if (c == 100) printf("\n");
		} while (filesize > 0);
	}
	return true;
}
void recvFile(struct Data *data,char path[])
{
	FILE *filehandle = fopen(path, "wb");
<<<<<<< HEAD
	
=======
>>>>>>> 660f14f767b27f91da68589bc8736bc0457de3b8
		if (filehandle != NULL)
	{
		bool ok = readfile(data, filehandle);
		fclose(filehandle);
	}
}