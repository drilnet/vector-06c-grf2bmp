
// �������� ����᪨� 䠩��� (GRF � BMP).
// Ukraine. (C) Demidov S.V.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---

	// ����㧨�� GRF-䠩�.
	extern unsigned char LoadGRF();

	// ��ᯠ������ GRF-䠩�.
	extern void UnpackingGRF();

	// ��४���஢��� 梥�.
	extern void CodeConversion();

	// ������ BMP-䠩�� �� ���.
	extern void SaveBMP();

	extern unsigned char buffergrf[32768]; // ���ᨢ ��� GRF-䠩��.
	extern unsigned short int sizegrf;     // ������ GRF-䠩�� � �����.
	extern unsigned long int sizedatabmp;  // ������ BMP-������.
	extern unsigned long int sizebmp;      // ������ BMP-䠩�� (��������� � �����).

void main(int argc, char* argv[])
{

	unsigned char addrcolorgrf; // ���� 梥� � buffergrf[32768].
	unsigned char* filenamegrf; // ��� GRF-䠩��.
	unsigned char addrfngrf;    // ���� � filenamegrf.

	// ��४���⥫� ���宥/��襥 ���७�� � GRF-䠩��.
	unsigned char ext;

	// ����� ��� BMP-䠩��.
	unsigned char filenamebmp[255] = { 0 };
	// ���� � ���ᨢ� filenamebmp[255].
	unsigned char addrfnb;

	filenamegrf = argv[1];

	printf("\n");
	printf("%s", "�������� ����᪨� 䠩��� (GRF � BMP).");
	printf("\n");
	printf("%s", "   Ukraine. (C) ������� �.�.");
	printf("\n");
	printf("\n");
	printf("%s", "   GRF - ����᪨� �ଠ� 䠩��� �����'�-06�.");
	printf("\n");
	printf("%s", "   BMP - ����᪨� �ଠ� 䠩��� Windows.");
	printf("\n");

	if (argv[1] == NULL)
		{
		// �᫨ � ��������� ��ப� ����.
		printf("\n");
		printf("%s", "   ��ଠ� ��������� ��ப�:");
		printf("\n");
		printf("%s", "      $ grf2bmp ���_䠩��.grf");
		printf("\n");
		printf("\n");
		}
		else
		{
		// �஢���� ���७�� GRF-䠩��,
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

		// �᫨ ���宥 ���७��.
		if (ext == 0)
			{
			printf("\n");
			printf("%s", "���宥 ���७�� � GRF-䠩��!");
			printf("\n");
			printf("\n");

			// �����襭��.
			exit(1);
			}

		// ---
		// | ����㧨�� GRF-䠩�.
		// ---
		LoadGRF(filenamegrf);

		printf("\n");

		printf("%s", "             ����: ");
		printf("%s", filenamegrf);
		printf("\n");

		// �뢥�� �� ���᮫� ࠧ��� GRF-䠩��.
		printf("%s", " ������ GRF-䠩��: ");
		printf("%d", sizegrf);
		printf("%s", " ");
		printf("%s", "����.");
		printf("\n");

		// ---
		// | ��ᯠ������ GRF-䠩�.
		// ---
		UnpackingGRF();

		// �뢥�� �� ���᮫� 梥� GRF-䠩��.
		printf("%s", "  ���� GRF-䠩��: ");

		for (addrcolorgrf = 0; addrcolorgrf < 16; addrcolorgrf++)
			{
			// �뢮� 梥� � Hex.
			if (buffergrf[addrcolorgrf] >=0 && buffergrf[addrcolorgrf] <= 15)
				{
				// ���� ��। �᫮�.
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
		// | ��४���஢��.
		// | ��࠭��� ������� �����'�-06� � BMP-�����.
		// ---
		CodeConversion();

		printf("%s", "������ BMP-������: ");
		printf("%u", sizedatabmp);
		printf("%s", " ���� (����� ���������).");
		printf("\n");

		// �����㥬 ���� ��ப� �� filenamegrf � filenamebmp.
		strncpy(filenamebmp, filenamegrf + 0, strlen(filenamegrf) - 4);

		addrfnb = strlen(filenamebmp);

		// ������� � ����� .bmp.
		filenamebmp[addrfnb++] = '.';
		filenamebmp[addrfnb++] = 'b';
		filenamebmp[addrfnb++] = 'm';
		filenamebmp[addrfnb++] = 'p';

		// ---
		// | ������ BMP-䠩�� �� ���.
		// ---
		SaveBMP(filenamebmp);

		printf("%s", " ������ BMP-䠩��: ");
		printf("%u", sizebmp);
		printf("%s", " ����.");
		printf("\n");

		printf("\n");

		printf("%s", "   ���� �������������! OK!");
		printf("\n");

		printf("\n");
		}
}