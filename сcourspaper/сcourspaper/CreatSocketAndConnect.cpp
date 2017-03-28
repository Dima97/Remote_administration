#include "Header.h"
void CreatSocketAndConnect(struct Data *data)
{
	printf("Enter server's IP: ");
	//scanf_s("%15s", data->IP, 16);
	strcpy(data->IP,"192.168.0.102");
	WSAStartup(0x0202, &(data->WSADat));
	gethostname(data->PCName, 30);
	data->sin.sin_family = AF_INET;
	data->sin.sin_addr.s_addr = inet_addr(data->IP);
	data->sin.sin_port = htons(2803);

	data->Sock = socket(AF_INET, SOCK_STREAM, 0);

	printf("connecting to server.. \n");

	if (connect(data->Sock, (SOCKADDR*)&(data->sin), sizeof(data->sin)) == SOCKET_ERROR) {
		printf("Connection error!\n");
		CloseConnect(data);
	}
	send(data->Sock, data->PCName, strlen(data->PCName) + 1, 0);
	recv(data->Sock, data->ServerName, 30, 0);

	printf("Connected to \"%s\"!\n", data->ServerName);
}