#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")

void main(void)
{
	char PCName[30], ServerName[30], Massage[200], IP[16] = { 0 };
	WSADATA WSADat;
	SOCKADDR_IN sin;
	SOCKET Sock;

	printf("Enter server's IP: ");
	scanf_s("%15s", IP, 16);
	WSAStartup(0x0202, &WSADat);
	gethostname(PCName, 30);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(IP);
	sin.sin_port = htons(2803);

	Sock = socket(AF_INET, SOCK_STREAM, 0);

	printf("connecting to server.. \n");

	if (connect(Sock, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("Connection error!\n");
		goto End;
	}
	send(Sock, PCName, strlen(PCName) + 1, 0);
	recv(Sock, ServerName,30,0);

	printf("Connected to \"%s\"!\n", ServerName);


	int Menu;
	do {
		printf("1 - send massage\n");
		printf("2 - get massage\n");
		printf("3 - Exit\n");

		printf("Make your selition: ");
		scanf_s("%i", &Menu);

		switch (Menu) {
		case 1:
			printf("Enter massage: ");
			scanf_s("%199s", Massage, 200);
			if (send(Sock, Massage, strlen(Massage) + 1, 0) != SOCKET_ERROR)
				printf("sent!\n");
			else printf("Error of sending! \n");
			break;
		case 2:
			if (recv(Sock, Massage, 200, 0) != SOCKET_ERROR)
			{
				printf("%s\n", Massage);
				_gettch();
			}
			else printf("Error of getting! \n");
			break;
		};
		printf("\n");
	} while (Menu != 3);
End:
	closesocket(Sock);
	WSACleanup();
	_gettch();
}