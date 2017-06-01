#include "Header.h"
void CreatSocketAndConnect(struct Data *data)
{
	setlocale(LC_CTYPE, "Russian"); 
	WSAStartup(0x0202, &(data->WSADat));

	gethostname(data->PCName, 30);
	data->sin.sin_family = AF_INET;
	data->sin.sin_addr.s_addr = 0;
	data->sin.sin_port = htons(2803);
	data->Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(data->Sock, (SOCKADDR*)&(data->sin), sizeof(data->sin));


	printf("wait of server...\n"); 

	listen(data->Sock, SOMAXCONN);
	data->Server = accept(data->Sock, (SOCKADDR*)&(data->sin), 0);
	recv(data->Server, data->ServerName, 30, 0);
	send(data->Server, data->PCName, strlen(data->PCName) + 1, 0);

	printf("Server (\"%s\") has connected!\n", data->ServerName);
}