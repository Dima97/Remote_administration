#include "Header.h"
int recieveData(struct Data *data)
{
	int totalRecieved = 0, arrived = 0;
	struct pollfd pfd;

	// �������������� ��������� ��� ������ ������� poll()
	pfd.fd = data->Sock; // ��������� ���������� ������ ������� ����������
	pfd.events = POLLIN | POLLHUP | POLLRDNORM;

	// ���� ���� �� ������� ��� ������
	while (totalRecieved < 100) {
		// ������� ������� � ������ � ��������� 100 �����������
		if (WSAPoll(&pfd, 1, 100) > 0) {
			// ��������� �����-�� ������� � �������� �������� ������
			arrived = recv(data->Sock, (char*)data->Massage + totalRecieved,100 - totalRecieved, MSG_PEEK);

			// ���� ������ �� ������ ����� ���� ��� poll() ������ �� �������
			// ��������� � ��� �������� ������ ����� ����������
			if (arrived == -1 || totalRecieved == arrived) {
				// ���������� ������� ���������� ������, ��� ������ �� ������� ����������
				totalRecieved = 0;
				break;
			}

			// ���������� �������� ������
			totalRecieved += arrived;
		}
	}

	return totalRecieved;
}