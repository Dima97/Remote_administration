#include "Header.h"
int recieveData(struct Data *data)
{
	int totalRecieved = 0, arrived = 0;
	struct pollfd pfd;

	// Подготавливаем структуру для вызова функции poll()
	pfd.fd = data->Sock; // Указываем дискриптор сокета который интересует
	pfd.events = POLLIN | POLLHUP | POLLRDNORM;

	// Цикл пока не получим все данные
	while (totalRecieved < 100) {
		// Ожидаем событие в сокете с таймаутом 100 миллисекунд
		if (WSAPoll(&pfd, 1, 100) > 0) {
			// Произошло какое-то событие — пытаемся получить данные
			arrived = recv(data->Sock, (char*)data->Massage + totalRecieved,100 - totalRecieved, MSG_PEEK);

			// Если данных не пришло после того как poll() вернул не нулевой
			// результат — это означает только обрыв соединения
			if (arrived == -1 || totalRecieved == arrived) {
				// Сбрасываем счётчик полученных данных, что скажет об разрыве соединения
				totalRecieved = 0;
				break;
			}

			// Продолжаем получать данные
			totalRecieved += arrived;
		}
	}

	return totalRecieved;
}