
// Конвертор графических файлов (GRF в BMP).
// Ukraine. (C) Demidov S.V.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---

	// Загрузить GRF-файл.
	extern unsigned char LoadGRF();

	// Распаковать GRF-файл.
	extern void UnpackingGRF();

	// Перекодировать цвета.
	extern void CodeConversion();

	// Запись BMP-файла на диск.
	extern void SaveBMP();

	extern unsigned char buffergrf[32768]; // Массив для GRF-файла.
	extern unsigned short int sizegrf;     // Размер GRF-файла в байтах.
	extern unsigned long int sizedatabmp;  // Размер BMP-данных.
	extern unsigned long int sizebmp;      // Размер BMP-файла (заголовок и данные).

void main(int argc, char* argv[])
{

	unsigned char addrcolorgrf; // Адрес цвета в buffergrf[32768].
	unsigned char* filenamegrf; // Имя GRF-файла.
	unsigned char addrfngrf;    // Адрес в filenamegrf.

	// Переключатель плохое/хорошее расширение у GRF-файла.
	unsigned char ext;

	// Здесь имя BMP-файла.
	unsigned char filenamebmp[255] = { 0 };
	// Адрес в массиве filenamebmp[255].
	unsigned char addrfnb;

	filenamegrf = argv[1];

	printf("\n");
	printf("%s", "Конвертер графических файлов (GRF в BMP).");
	printf("\n");
	printf("%s", "   Ukraine. (C) Демидов С.В.");
	printf("\n");
	printf("\n");
	printf("%s", "   GRF - графический формат файлов Вектор'а-06Ц.");
	printf("\n");
	printf("%s", "   BMP - графический формат файлов Windows.");
	printf("\n");

	if (argv[1] == NULL)
		{
		// Если в командной строке пусто.
		printf("\n");
		printf("%s", "   Формат командной строки:");
		printf("\n");
		printf("%s", "      $ grf2bmp имя_файла.grf");
		printf("\n");
		printf("\n");
		}
		else
		{
		// Проверить расширение GRF-файла,
		addrfngrf = strlen(filenamegrf) - 3;

		if (filenamegrf[addrfngrf] == 'G' || filenamegrf[addrfngrf] == 'g')
			{
			addrfngrf++;
			if (filenamegrf[addrfngrf] == 'R' || filenamegrf[addrfngrf] == 'r')
				{
				addrfngrf++;
				if (filenamegrf[addrfngrf] == 'F' || filenamegrf[addrfngrf] == 'f')
					{
					ext = 1; // Good.
					}
					else
					{
					ext = 0;
					}
				}
				else
				{
				ext = 0;
				}
			}
			else
			{
			ext = 0;
			}

		// Если плохое расширение.
		if (ext == 0)
			{
			printf("\n");
			printf("%s", "Плохое расширение у GRF-файла!");
			printf("\n");
			printf("\n");

			// Завершение.
			exit(1);
			}

		// ---
		// | Загрузить GRF-файл.
		// ---
		LoadGRF(filenamegrf);

		printf("\n");

		printf("%s", "             Файл: ");
		printf("%s", filenamegrf);
		printf("\n");

		// Вывести на консоль размер GRF-файла.
		printf("%s", " Размер GRF-файла: ");
		printf("%d", sizegrf);
		printf("%s", " ");
		printf("%s", "байт.");
		printf("\n");

		// ---
		// | Распаковать GRF-файл.
		// ---
		UnpackingGRF();

		// Вывести на консоль цвета GRF-файла.
		printf("%s", "  Цвета GRF-файла: ");

		for (addrcolorgrf = 0; addrcolorgrf < 16; addrcolorgrf++)
			{
			// Вывод цвета в Hex.
			if (buffergrf[addrcolorgrf] >=0 && buffergrf[addrcolorgrf] <= 15)
				{
				// Ноль перед числом.
				printf("%s", "0");
				}

			printf("%X", buffergrf[addrcolorgrf]);
			printf("%s", "H");

			if (addrcolorgrf != 15)
				{
				printf("%s", " ");
				}
				else
				{
				printf("%s", ".");
				}
			}

		printf("\n");

		// ---
		// | Перекодировка.
		// | Экранная область Вектор'а-06Ц в BMP-данные.
		// ---
		CodeConversion();

		printf("%s", "Размер BMP-данных: ");
		printf("%u", sizedatabmp);
		printf("%s", " байт (минус заголовок).");
		printf("\n");

		// Копируем часть строки из filenamegrf в filenamebmp.
		strncpy(filenamebmp, filenamegrf + 0, strlen(filenamegrf) - 4);

		addrfnb = strlen(filenamebmp);

		// Дописать в конец .bmp.
		filenamebmp[addrfnb++] = '.';
		filenamebmp[addrfnb++] = 'b';
		filenamebmp[addrfnb++] = 'm';
		filenamebmp[addrfnb++] = 'p';

		// ---
		// | Запись BMP-файла на диск.
		// ---
		SaveBMP(filenamebmp);

		printf("%s", " Размер BMP-файла: ");
		printf("%u", sizebmp);
		printf("%s", " байт.");
		printf("\n");

		printf("\n");

		printf("%s", "   ФАЙЛ КОНВЕРТИРОВАН! OK!");
		printf("\n");

		printf("\n");
		}
}