#include "Header.h"
void mouseClick(struct Data *data)
{
<<<<<<< HEAD
=======
	//system("cls");
>>>>>>> 660f14f767b27f91da68589bc8736bc0457de3b8
	HANDLE hStdin;
	DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
	INPUT_RECORD irInBuf[128];
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdin, &fdwSaveOldMode);
<<<<<<< HEAD
	
	FlushConsoleInputBuffer(hStdin);
	SetConsoleMode(hStdin, ENABLE_MOUSE_INPUT);
=======
	fdwMode = fdwSaveOldMode & ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);
>>>>>>> 660f14f767b27f91da68589bc8736bc0457de3b8
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
<<<<<<< HEAD
				case MOUSE_MOVED: {
					strcat(data->Massage, "M");
					char buffer[20];
					pos[0] = irInBuf[i].Event.MouseEvent.dwMousePosition.X;
					pos[1] = irInBuf[i].Event.MouseEvent.dwMousePosition.Y;
					strcat(data->Massage, itoa(pos[0], buffer, 10));
					strcat(data->Massage, " ");
					strcat(data->Massage, itoa(pos[1], buffer, 10));
					send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0);
					break;
				}
				case DOUBLE_CLICK:
				{
					strcat(data->Massage, "D");
					char buffer[20];
					pos[0] = irInBuf[i].Event.MouseEvent.dwMousePosition.X;
					pos[1] = irInBuf[i].Event.MouseEvent.dwMousePosition.Y;
					strcat(data->Massage, itoa(pos[0], buffer, 10));
					strcat(data->Massage, " ");
					strcat(data->Massage, itoa(pos[1], buffer, 10));
					send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0);
					break;
				}
				    default: {
					strcat(data->Massage, "C");
					char buffer[20];
					pos[0] = irInBuf[i].Event.MouseEvent.dwMousePosition.X;
					pos[1] = irInBuf[i].Event.MouseEvent.dwMousePosition.Y;
					strcat(data->Massage, itoa(pos[0], buffer, 10));
					strcat(data->Massage, " ");
					strcat(data->Massage, itoa(pos[1], buffer, 10));
					send(data->Sock, data->Massage, strlen(data->Massage) + 1, 0);
					break;
				}
				}
				
			}
			if (irInBuf[i].EventType == KEY_EVENT)
			{
				if (irInBuf[i].Event.KeyEvent.uChar.AsciiChar == 'q');
				{
					strcpy(data->Massage, "W");
					send(data->Sock, data->Massage, 1, 0);
					freopen("CONIN$", "r+", stdin);
					return;
				}
			}
		}
	}
	_getch();
=======
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

>>>>>>> 660f14f767b27f91da68589bc8736bc0457de3b8
}