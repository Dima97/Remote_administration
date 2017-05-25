#include "Header.h"
HHOOK MousHook;
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
		switch (Menu)
		{
		case 1: {
			printf("enter command ");
			scanf_s("%199s", data->Massage, 200);
			switch (atoi(data->Massage))
			{
			/*case 1:
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
				break;*/
			case 2:
			{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
				break;
			}
			case 3:
			{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
				break;
			}
			case 1:
				{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
				break;
			}
			case 4:
			{
				printf("%s", data->Massage);
				printf("enter path");
				scanf("%s", path);
				strcat(data->Massage, path);
				break;
			}
			default: 
			{
				if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
					printf("Sent!\n");
				else printf("Error of sending!\n");
				break;
			}
		}
			break;
		}
		case 2:
		{
			printf("enter command ");
			scanf_s("%199s", data->Massage, 200);
			switch (atoi(data->Massage))
			{
			case 1:
			{
				printf("enter path for downloading");
				scanf("%s", path);
				recvFile(data, path);
				printf("file downloaded!");
				break;
			}
			case 2: 
			{
				system("cls");
				recv(data->Sock, data->Massage, 387, 0);
				printf("%s\n", data->Massage);
				break;
			}
			default: {
				recv(data->Sock, data->Massage, 100, 0);
				printf("%s\n", data->Massage);
				break;
			}
			}
			break;
		}
		case 3:
		{
			mouseClick(data);
			break;

		}
		}
		if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
			printf("Sent!\n");
		else printf("Error of sending!\n");
	} while (Menu != 0);
}