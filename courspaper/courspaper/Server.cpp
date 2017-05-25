#include "Header.h"

void main()
{
	struct Data data;
	HWND hwnd;
	char Title[1024];
	GetConsoleTitle(Title, 1024); // Узнаем имя окна
	hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
	MoveWindow(hwnd, 0, 0, 800, 500, TRUE);
	CreatSocketAndConnect(&data);

	Menu(&data);

	CloseConnect(&data);
	_getch();
}
