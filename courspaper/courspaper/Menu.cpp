#include "Header.h"
void Menu(struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	char path[100];
	int Menu = 100;
	do {
		printf("1 - reboot the PC\n");
		printf("2 - shutdown the PC\n");
		printf("3 - Exit of systeme PC\n");
		printf("4 - Open CDROM in PC\n");
		printf("5 - Exit\n\n");
		printf("8-createfile\n");
		printf("7-delete file\n");

		printf("1 - get command\n0 - close the programm ");
		scanf("%i", &Menu);

		if (Menu == 1)
		{
			printf("enter command ");
			scanf_s("%199s", data->Massage, 200);
			if (atoi(data->Massage) == 8)
			{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
			}
			if (atoi(data->Massage) == 7)
			{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
			}
			if (atoi(data->Massage) == 0)
			{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
			}
			if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
				printf("Sent!\n");
			else printf("Error of sending!\n");
		}
		if (Menu == 0)
		{
			printf("enter path for downloading");
			scanf("%s", path);
			recvFile(data,path);
			printf("tip prinal");
		}
		//recv(data->Sock, data->Massage, 100, 0);
		//printf("%s\n", data->Massage);
	} while (Menu != 0);
}