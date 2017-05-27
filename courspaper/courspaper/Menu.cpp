#include "Header.h"
#include<string>
void SendMsg(struct Data *data)
{
	if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
			printf("Sent!\n");
		else printf("Error of sending!\n");
}
void Menu(struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	char command[100];
	char path[100];
	while (1) {

		//scanf("%i", &Menu);
		//switch (Menu)
		//{
		//case 1: {
		//	printf("enter command ");
		//	scanf_s("%199s", data->Massage, 200);
		//	switch (atoi(data->Massage))
		//	{
		//	/*case 1:
		//		printf("%s", data->Massage);
		//		printf("enter path");
		//		scanf("%s", path);
		//		strcat(data->Massage, path);
		//		break;*/
		//	case 2:
		//	{
		//		printf("%s", data->Massage);
		//		printf("enter path");
		//		scanf("%s", path);
		//		strcat(data->Massage, path);
		//		break;
		//	}
		//	/*case 3:
		//	{
		//		printf("%s", data->Massage);
		//		printf("enter path");
		//		scanf("%s", path);
		//		strcat(data->Massage, path);
		//		break;
		//	}*/
		//	case 3:
		//	{
		//		if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
		//			printf("Sent!\n");
		//		else printf("Error of sending!\n");
		//		do {
		//			recv(data->Sock, data->Massage, 100, 0);
		//			printf("%s\n", data->Massage);
		//		} while (strcmp(data->Massage, "Program Manager") != 0);
		//		break;
		//	}
		//	case 1:
		//		{
		//		printf("%s", data->Massage);
		//		printf("enter path");
		//		scanf("%s", path);
		//		strcat(data->Massage, path);
		//		break;
		//	}
		//	case 4:
		//	{
		//		printf("%s", data->Massage);
		//		printf("enter path");
		//		scanf("%s", path);
		//		strcat(data->Massage, path);
		//		break;
		//	}
		///*	default: 
		//	{
		//		if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
		//			printf("Sent!\n");
		//		else printf("Error of sending!\n");
		//		break;
		//	}*/
		//}
		//	break;
		//}
		//case 2:
		//{
		//	printf("enter command ");
		//	scanf_s("%199s", data->Massage, 200);
		//	switch (atoi(data->Massage))
		//	{
		//	case 1:
		//	{
		//		printf("enter path for downloading");
		//		scanf("%s", path);
		//		recvFile(data, path);
		//		printf("file downloaded!");
		//		break;
		//	}
		//	case 2: 
		//	{
		//		system("cls");
		//		recv(data->Sock, data->Massage, 387, 0);
		//		printf("%s\n", data->Massage);
		//		break;
		//	}
		//	case 3:
		//	{
		//		do {
		//			recv(data->Sock, data->Massage, 100, 0);
		//			printf("%s\n", data->Massage);
		//		} while (strcmp(data->Massage, "Program Manager") != 0);
		//		break;
		//	}
		//	default: {
		//		recv(data->Sock, data->Massage, 100, 0);
		//		printf("%s\n", data->Massage);
		//		break;
		//	}
		//	}
		//	break;
		//}
		//case 3:
		//{
		//	mouseClick(data);
		//	break;

		//}
		//}
		//if (send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
		//	printf("Sent!\n");
		//else printf("Error of sending!\n");
		printf("$ ");
		scanf("%s", &command);
		if (!strcmp(command, "mkfile")) {
			scanf("%s", &command);
			strcpy(data->Massage, "1");
			strcat(data->Massage, command);
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "delfile")) {
			scanf("%s", &command);
			strcpy(data->Massage, "2");
			strcat(data->Massage, command);
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "execpr")) {
			scanf("%s", &command);
			strcpy(data->Massage, "3");
			strcat(data->Massage, command);
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "closepr")) {
			scanf("%s", &command);
			strcpy(data->Massage, "4");
			strcat(data->Massage, command);
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "getfile")) {
			scanf("%s", &command);
			strcpy(data->Massage, "5");
			strcat(data->Massage, command);
			SendMsg(data);
			printf("enter name in your PC");
			scanf("%s", path);
			char str[100] = "C:\\RemoteAdministration\\";
			strcat(str, path);
			recvFile(data, str);
			printf("file downloaded!\n");
			continue;
		}
		else if (!strcmp(command, "getcursor")) {
			strcpy(data->Massage, "6");
			SendMsg(data);
			mouseClick(data);
			continue;
		}
		else if (!strcmp(command, "getsystinfo")) {
			strcpy(data->Massage, "7");
			SendMsg(data);
			system("cls");
			recv(data->Sock, data->Massage, 387, 0);
			printf("%s\n", data->Massage);
			continue;
		}
		else if (!strcmp(command, "getinfotasks")) {
			strcpy(data->Massage, "8");
			SendMsg(data);
			do {
				recv(data->Sock, data->Massage, 100, 0);
				printf("%s\n", data->Massage);
			} while (strcmp(data->Massage, "Program Manager") != 0);
			continue;
		}
		else if (!strcmp(command, "reboot")) {
			strcpy(data->Massage, "9");
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "shdown")) {
			strcpy(data->Massage, "a");
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "exitsyst")) {
			strcpy(data->Massage, "b");
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "opencd")) {
			strcpy(data->Massage, "c");
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "exit")) {
			exit(0);
		}
		else if (!strcmp(command, "cls")) {
			system("cls");
			continue;
		}
		else if (!strcmp(command, "copyinfold")) {
			scanf("%s", &command);
			strcpy(data->Massage, "e");
			strcat(data->Massage, command);
			SendMsg(data);
			continue;
		}
		else if (!strcmp(command, "showfile")) {
			strcpy(data->Massage, "d");
			SendMsg(data);
			do {
				recv(data->Sock, data->Massage, 100, 0);
				if (strcmp(data->Massage, "0") == 0) break;
				printf("%s\n", data->Massage);
			} while (1);
			continue;
		}
		else printf(" Unknown command");
		recv(data->Sock, data->Massage, 100, 0);
		printf("%s\n", data->Massage);
		continue;
	}
}