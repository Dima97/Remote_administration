#include "Header.h"

void main(void)
{
	struct Data data;
	CreatSocketAndConnect(&data);

	Menu(&data);

	CloseConnect(&data);
}