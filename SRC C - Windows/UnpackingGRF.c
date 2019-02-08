
// Распаковка GRF файла.

#include <stdio.h>
#include <stdlib.h>

	extern unsigned char buffergrf[32768]; // Массив для GRF файла.
	extern unsigned short int sizegrf; // Размер GRF файла в байтах.

	// Экранная область Вектор-06Ц.
	unsigned char screen_vector_8000_FFFF[32768];

void UnpackingGRF()
{
	unsigned short int addrgrf; // Адрес в массиве buffergrf.
	unsigned short int addrvcs; // Адрес в массиве экранная область Вектор-06Ц.

	unsigned char bit_s; // Есть ли повторяющиеся байты, 0 - нет, 1 - есть.
	unsigned char cb;    // Счётчик 
	unsigned char tb;    // Сколько не повторяющихся/повторяющихся байт.

//	printf("%s", "Размер GRF данных: ");
//	printf("%u", sizegrf - 16);
//	printf("%s", " байт (минус цвета, но плюс мусор).");
//	printf("\n");

	addrvcs = 0;

	// Распаковка (распаковка в screen_vector_8000_FFFF[addrvcs]).
	for (addrgrf = 16; addrgrf < sizegrf; addrgrf++)
		{

		// Если встретится 0, значит прервать цикл (конец распаковки).
		if (buffergrf[addrgrf] == 0)
			{
			break;
			}

		bit_s = 128 & buffergrf[addrgrf]; // 80H и buffergrf[addrgrf].

		if (bit_s == 128)
			{
			// Не повторяющиеся байты.
			// ---

			tb = buffergrf[addrgrf];
			tb = 127 & tb; // 7F и tb.

			for (cb = 0; cb < tb; cb++)
				{
				addrgrf++;

				if (addrvcs == 32768)
					{
					printf("\n");
					printf("%s", "Ошибка GRF файла!");
					printf("\n");
					printf("\n");

					// Завершение.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = buffergrf[addrgrf];

				addrvcs++;
				}
			}
			else
			{
			// Повторяющиеся байты.
			// ---

			tb = buffergrf[addrgrf];

			addrgrf++;

			for (cb = 0; cb < tb; cb++)
				{

				if (addrvcs == 32768)
					{
					printf("\n");
					printf("%s", "Ошибка GRF файла!");
					printf("\n");
					printf("\n");

					// Завершение.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = buffergrf[addrgrf];

				addrvcs++;
				}
			}

		}

//	printf("%s", "      Распаковано: ");
//	printf("%u", addrvcs);
//	printf("%s", " байт.");
//	printf("\n");

	if (addrvcs != 32768)
		{
		printf("\n");
		printf("%s", "Ошибка GRF файла!");
		printf("\n");
		printf("\n");

		// Завершение.
		exit(1);
		}

	printf("%s","Размер GRF данных: ");
	printf("%u", addrgrf - 16);
	printf("%s", " байт (минус цвета, минус мусор).");
	printf("\n");
}