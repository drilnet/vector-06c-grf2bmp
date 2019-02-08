
// �⥭�� GRF 䠩�� � ������.

#include <stdio.h>
#include <stdlib.h>

// ����� � ��६���� �� ��㣨� �ணࠬ�.
	unsigned char buffergrf[32768]; // ���ᨢ ��� GRF 䠩��.
	unsigned short int sizegrf; // ������ GRF 䠩�� � �����.

void LoadGRF(unsigned char* filename)
{

	unsigned short int addrgrf; // ���� � ���ᨢ� buffergrf.
	int byte; // ����騩 ���� �� GRF 䠩��.

	FILE *filed = NULL;
	// ����⨥ ����筮�� 䠩�� (rb).
	filed = fopen(filename, "rb");

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

	addrgrf = 0; sizegrf = 0;

	while (1)
	{
	// �⥭�� ������ ���� �� 䠩��.
	byte = getc(filed);

	if (byte == EOF)
		{
		if (feof(filed) != 0)
			{
			// �⥭�� 䠩�� �����稫���.
			break;
			}
			else
			{
			// �訡�� �⥭�� �� 䠩��.
			printf("\n");

			printf("%s", "��������!");
			printf("\n");

			printf("%s", "�訡�� �⥭�� GRF 䠩��!");
			printf("\n");

			printf("\n");

			// �����襭��.
			exit(1);
			}
		}

	// ���誮� ����让 䠩�.
	if (sizegrf == 32768)
		{

		// �����⨥ 䠩��.
		fclose(filed);

		printf("\n");
		printf("%s", "�訡�� GRF 䠩��!");
		printf("\n");
		printf("\n");

		// �����襭��.
		exit(1);
		}

	buffergrf[addrgrf] = byte;
	addrgrf++;
	sizegrf++;
	}

	// �����⨥ 䠩��.
	fclose(filed);

}