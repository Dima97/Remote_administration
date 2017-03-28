#include "Header.h"
void Menu(struct Data *data)
{
	int Menu = 0;
	while (1) {
		if (recv(data->Sock, data->Massage, 200, 0) != SOCKET_ERROR)
		{
			printf("%s\n", data->Massage);
			Menu = atoi(data->Massage);
			switch (Menu)
			{
			case 1:
				RebootPC();
				break;
			case 2:
				ShutDownPC();
				break;
			case 3:
				ExitSystemePC();
				break;
			case 4:
				OpenCD_ROM();
				break;
			case 5:
				ExitFunction();
				break;
			}
		}
		else {
			printf("Error of getting! \n");
			break;
		}
	}
}