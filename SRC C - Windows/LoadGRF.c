
// Чтение GRF файла в память.

#include <stdio.h>
#include <stdlib.h>

// Доступ к переменным из других программ.
	unsigned char buffergrf[32768]; // Массив для GRF файла.
	unsigned short int sizegrf; // Размер GRF файла в байтах.

void LoadGRF(unsigned char* filename)
{

	unsigned short int addrgrf; // Адрес в массиве buffergrf.
	int byte; // Текущий байт из GRF файла.

	FILE *filed = NULL;
	// Открытие двоичного файла (rb).
	filed = fopen(filename, "rb");

	if (filed == NULL)
		{
		printf("\n");

		printf("%s", "Внимание!");
		printf("\n");

		printf("%s", "Ошибка открытия файла ");
		printf("%s", filename);
		printf("%s", ".");
		printf("\n");

		printf("\n");

		// Завершение с кодом ошибки 1.
		exit(1);
		}

	addrgrf = 0; sizegrf = 0;

	while (1)
	{
	// Чтение одного байта из файла.
	byte = getc(filed);

	if (byte == EOF)
		{
		if (feof(filed) != 0)
			{
			// Чтение файла закончилось.
			break;
			}
			else
			{
			// Ошибка чтения из файла.
			printf("\n");

			printf("%s", "Внимание!");
			printf("\n");

			printf("%s", "Ошибка чтения GRF файла!");
			printf("\n");

			printf("\n");

			// Завершение.
			exit(1);
			}
		}

	// Слишком большой файл.
	if (sizegrf == 32768)
		{

		// Закрытие файла.
		fclose(filed);

		printf("\n");
		printf("%s", "Ошибка GRF файла!");
		printf("\n");
		printf("\n");

		// Завершение.
		exit(1);
		}

	buffergrf[addrgrf] = byte;
	addrgrf++;
	sizegrf++;
	}

	// Закрытие файла.
	fclose(filed);

}