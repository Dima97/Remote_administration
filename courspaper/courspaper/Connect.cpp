#include "Header.h"
void CreatSocketAndConnect(struct Data *data)
{
	WSAStartup(0x0202, &(data->WSADat));

	gethostname(data->PCName, 30);
	data->sin.sin_family = AF_INET;
	data->sin.sin_addr.s_addr = 0;
	data->sin.sin_port = htons(2803);
	data->Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(data->Sock, (SOCKADDR*)&(data->sin), sizeof(data->sin));


	printf("wait of client...\n");

	listen(data->Sock, SOMAXCONN);
	data->Client = accept(data->Sock, (SOCKADDR*)&(data->sin), 0);
	recv(data->Client, data->ClientName, 30, 0);
	send(data->Client, data->PCName, strlen(data->PCName) + 1, 0);

	printf("Client (\"%s\") has connected!\n", data->ClientName);
}