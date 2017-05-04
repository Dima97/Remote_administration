#include "Header.h"
void CloseConnect(struct Data *data)
{
	closesocket(data->Sock);
	closesocket(data->Server);
	WSACleanup();
}
