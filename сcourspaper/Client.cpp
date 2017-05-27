#include "Header.h"

void main(void)
{
	struct Data data;

	CreateDirectory("D:\\RemoteAdministration", NULL);

	CreatSocketAndConnect(&data);

	Menu(&data);

	CloseConnect(&data);
	return;
}