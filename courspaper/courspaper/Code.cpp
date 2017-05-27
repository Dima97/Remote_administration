#include "Header.h"
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
		} while (filesize > 0);
	}
	return true;
}
void recvFile(struct Data *data,char path[])
{
	FILE *filehandle = fopen(path, "wb");
		if (filehandle != NULL)
	{
		bool ok = readfile(data, filehandle);
		fclose(filehandle);
	}
}