#include "Header.h"
void Menu(struct Data *data)
{
	int Menu = 0;
	while (1) {
		if (recv(data->Server, data->Massage, 200, 0) != SOCKET_ERROR)
		{
			printf("%s\n", data->Massage);
			//Menu = atoi(data->Massage[0]);
			switch (data->Massage[0])
			{
			case '1':
				RebootPC();
				break;
			case '2':
				ShutDownPC();
				break;
			case '3':
				ExitSystemePC();
				break;
			case '4':
				OpenCD_ROM();
				break;
			case '5':
				ExitFunction();
				break;
			case '8':
				CreatFile(data->Massage,data);
				break;
			case '7':
				DelFile(data->Massage,data);
			case '6':
				WorkWithCursor(data);
			case '0':
				sendFileFunction(data->Massage,data);
			}
		}
		else {
			printf("Error of getting! \n");
			break;
		}
	}
}