
// Запись BMP-файла на диск.

#include <stdio.h>
#include <stdlib.h>

	extern unsigned long int sizedatabmp; // Размер BMP-данных.
	extern unsigned char bufferbmp[196608]; // Массив с данными (без заголовка).

	unsigned long int sizebmp; // Размер BMP-файла (заголовок и данные).

void SaveBMP(unsigned char* filename)
{

	// Заголовок BMP файла.
	unsigned char array_tiltle_bmp[122] = {

	0x42, 0x4d, 0x7a, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x00, 0x00, 0x00, 0x6c, 0x00, // 0000.
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, // 0010.
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00, // 0020.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x47, 0x52, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0030.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0040.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0050.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 0060.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                                      // 0070.

	};

	unsigned char addr_title_bmp; // Адрес для array_tiltle_bmp[122].
	unsigned long int addr_data_bmp; // Адрес для bufferbmp[196608].
	unsigned char byte; // Текущий байт для записи.

	FILE *filed = NULL;
	// Открытие двоичного файла (wb).
	filed = fopen(filename, "wb");

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

	// Записываем заголовок.
	for (addr_title_bmp = 0; addr_title_bmp < 122; addr_title_bmp++)
		{
		byte = array_tiltle_bmp[addr_title_bmp];

		// Запись одного байта в файл.
		byte = putc(byte, filed);

		if (byte == EOF)
			{
			// Ошибка записи.
			printf("\n");

			printf("%s", "Внимание!");
			printf("\n");

			printf("%s", "Ошибка записи!");
			printf("\n");

			printf("\n");

			// Завершение.
			exit(1);
			}

		}

	// Записываем сами данные.
	for (addr_data_bmp = 0; addr_data_bmp < sizedatabmp; addr_data_bmp++)
		{
		byte = bufferbmp[addr_data_bmp];

		// Запись одного байта в файл.
		byte = putc(byte, filed);

		if (byte == EOF)
			{
			// Ошибка записи.
			printf("\n");

			printf("%s", "Внимание!");
			printf("\n");

			printf("%s", "Ошибка записи!");
			printf("\n");

			printf("\n");

			// Завершение.
			exit(1);
			}

		}

	// Закрытие файла.
	fclose(filed);

	sizebmp = 122 + sizedatabmp;
}