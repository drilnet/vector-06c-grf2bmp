
// ��ᯠ����� GRF 䠩��.

#include <stdio.h>
#include <stdlib.h>

	extern unsigned char buffergrf[32768]; // ���ᨢ ��� GRF 䠩��.
	extern unsigned short int sizegrf; // ������ GRF 䠩�� � �����.

	// ��࠭��� ������� �����-06�.
	unsigned char screen_vector_8000_FFFF[32768];

void UnpackingGRF()
{
	unsigned short int addrgrf; // ���� � ���ᨢ� buffergrf.
	unsigned short int addrvcs; // ���� � ���ᨢ� �࠭��� ������� �����-06�.

	unsigned char bit_s; // ���� �� �������騥�� �����, 0 - ���, 1 - ����.
	unsigned char cb;    // ����稪 
	unsigned char tb;    // ����쪮 �� �����������/����������� ����.

//	printf("%s", "������ GRF ������: ");
//	printf("%u", sizegrf - 16);
//	printf("%s", " ���� (����� 梥�, �� ���� ����).");
//	printf("\n");

	addrvcs = 0;

	// ��ᯠ����� (�ᯠ����� � screen_vector_8000_FFFF[addrvcs]).
	for (addrgrf = 16; addrgrf < sizegrf; addrgrf++)
		{

		// �᫨ �������� 0, ����� ��ࢠ�� 横� (����� �ᯠ�����).
		if (buffergrf[addrgrf] == 0)
			{
			break;
			}

		bit_s = 128 & buffergrf[addrgrf]; // 80H � buffergrf[addrgrf].

		if (bit_s == 128)
			{
			// �� �������騥�� �����.
			// ---

			tb = buffergrf[addrgrf];
			tb = 127 & tb; // 7F � tb.

			for (cb = 0; cb < tb; cb++)
				{
				addrgrf++;

				if (addrvcs == 32768)
					{
					printf("\n");
					printf("%s", "�訡�� GRF 䠩��!");
					printf("\n");
					printf("\n");

					// �����襭��.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = buffergrf[addrgrf];

				addrvcs++;
				}
			}
			else
			{
			// �������騥�� �����.
			// ---

			tb = buffergrf[addrgrf];

			addrgrf++;

			for (cb = 0; cb < tb; cb++)
				{

				if (addrvcs == 32768)
					{
					printf("\n");
					printf("%s", "�訡�� GRF 䠩��!");
					printf("\n");
					printf("\n");

					// �����襭��.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = buffergrf[addrgrf];

				addrvcs++;
				}
			}

		}

//	printf("%s", "      ��ᯠ������: ");
//	printf("%u", addrvcs);
//	printf("%s", " ����.");
//	printf("\n");

	if (addrvcs != 32768)
		{
		printf("\n");
		printf("%s", "�訡�� GRF 䠩��!");
		printf("\n");
		printf("\n");

		// �����襭��.
		exit(1);
		}

	printf("%s","������ GRF ������: ");
	printf("%u", addrgrf - 16);
	printf("%s", " ���� (����� 梥�, ����� ����).");
	printf("\n");
}