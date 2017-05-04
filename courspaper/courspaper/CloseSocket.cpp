#include "Header.h"
void CloseConnect(struct Data *data)
{
	closesocket(data->Sock);
	WSACleanup();
}