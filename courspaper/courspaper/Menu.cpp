#include "Header.h"
void Menu(struct Data *data)
{
	int Menu = 100;
	do {
		printf("1 - reboot the PC\n");
		printf("2 - shutdown the PC\n");
		printf("3 - Exit of systeme PC\n");
		printf("4 - Open CDROM in PC\n");
		printf("5 - Exit\n\n");

		printf("1 - get command\n0 - close the programm ");
		scanf("%i", &Menu);

		if (Menu == 1)
		{
			printf("enter command");
			scanf_s("%199s", data->Massage, 200);
			if (send(data->Client, data->Massage, strlen(data->Massage) + 1, 0) != SOCKET_ERROR)
				printf("Sent!\n");
			else printf("Error of sending!\n");
		}
	} while (Menu != 0);
}