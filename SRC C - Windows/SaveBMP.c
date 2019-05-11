
// ������ BMP-䠩�� �� ���.

#include <stdio.h>
#include <stdlib.h>

	extern unsigned long int sizedatabmp; // ������ BMP-������.
	extern unsigned char bufferbmp[196608]; // ���ᨢ � ����묨 (��� ���������).

	unsigned long int sizebmp; // ������ BMP-䠩�� (��������� � �����).

void SaveBMP(unsigned char* filename)
{

	// ��������� BMP 䠩��.
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

	unsigned char addr_title_bmp; // ���� ��� array_tiltle_bmp[122].
	unsigned long int addr_data_bmp; // ���� ��� bufferbmp[196608].
	unsigned char byte; // ����騩 ���� ��� �����.

	FILE *filed = NULL;
	// ����⨥ ����筮�� 䠩�� (wb).
	filed = fopen(filename, "wb");

	if (filed == NULL)
		{
		printf("\n");

		printf("%s", "��������!");
		printf("\n");

		printf("%s", "�訡�� ������ 䠩�� ");
		printf("%s", filename);
		printf("%s", ".");
		printf("\n");

		printf("\n");

		// �����襭�� � ����� �訡�� 1.
		exit(1);
		}

	// �����뢠�� ���������.
	for (addr_title_bmp = 0; addr_title_bmp < 122; addr_title_bmp++)
		{
		byte = array_tiltle_bmp[addr_title_bmp];

		// ������ ������ ���� � 䠩�.
		byte = putc(byte, filed);

		if (byte == EOF)
			{
			// �訡�� �����.
			printf("\n");

			printf("%s", "��������!");
			printf("\n");

			printf("%s", "�訡�� �����!");
			printf("\n");

			printf("\n");

			// �����襭��.
			exit(1);
			}

		}

	// �����뢠�� ᠬ� �����.
	for (addr_data_bmp = 0; addr_data_bmp < sizedatabmp; addr_data_bmp++)
		{
		byte = bufferbmp[addr_data_bmp];

		// ������ ������ ���� � 䠩�.
		byte = putc(byte, filed);

		if (byte == EOF)
			{
			// �訡�� �����.
			printf("\n");

			printf("%s", "��������!");
			printf("\n");

			printf("%s", "�訡�� �����!");
			printf("\n");

			printf("\n");

			// �����襭��.
			exit(1);
			}

		}

	// �����⨥ 䠩��.
	fclose(filed);

	sizebmp = 122 + sizedatabmp;
}