#include "Header.h"
void CreatSocketAndConnect(struct Data *data)
{
	printf("Enter client's IP: ");
	// scanf_s("%15s", data->IP, 16);
	strcpy(data->IP, "192.168.0.111");

	WSAStartup(0x0202, &(data->WSADat));

	gethostname(data->PCName, 30);
	data->sin.sin_family = AF_INET;
	data->sin.sin_addr.s_addr = inet_addr(data->IP);
	data->sin.sin_port = htons(2803);
	data->Sock = socket(AF_INET, SOCK_STREAM, 0);

	printf("connecting to client... \n");
		if (connect(data->Sock, (SOCKADDR*)&(data->sin), sizeof(data->sin)) == SOCKET_ERROR) {
			system("cls");
			CloseConnect(data);
		}
	send(data->Sock, data->PCName, strlen(data->PCName) + 1, 0);
	recv(data->Sock, data->ClientName, 30, 0);
	if (strlen(data->ClientName) > 30) CreatSocketAndConnect(data);
	system("cls");
	printf("Connected to \"%s\"!\n", data->ClientName);
	return;
}