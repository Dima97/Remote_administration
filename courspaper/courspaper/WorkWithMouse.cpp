#include "Header.h"
void mouseClick(struct Data *data)
{
	//system("cls");
	HANDLE hStdin;
	DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
	INPUT_RECORD irInBuf[128];
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdin, &fdwSaveOldMode);
	fdwMode = fdwSaveOldMode & ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);
	int pos[2];
	while (1)
	{
		ReadConsoleInput(hStdin, irInBuf, 250, &cNumRead);
		for (i = 0; i < cNumRead; i++)
		{
			if (irInBuf[i].EventType == MOUSE_EVENT)
			{
				strcpy(data->Massage, "");
				switch (irInBuf[i].Event.MouseEvent.dwEventFlags)
				{
				case MOUSE_MOVED: strcat(data->Massage,"M");
					break;
				case DOUBLE_CLICK: strcat(data->Massage,"C");
					break;
				case MOUSE_WHEELED: strcat(data->Massage,"W");
					break;
				}char buffer[20];
				pos[0] = irInBuf[i].Event.MouseEvent.dwMousePosition.X;
				pos[1] = irInBuf[i].Event.MouseEvent.dwMousePosition.Y;
				strcat(data->Massage,itoa(pos[0],buffer,10));
				strcat(data->Massage, " ");
				strcat(data->Massage, itoa(pos[1], buffer, 10));
				send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0);
			}
		}
		Sleep(100);
	}

}