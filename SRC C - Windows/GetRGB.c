
#include <stdio.h>

// ����� � ��६���� �� ��㣨� �ணࠬ�.
	unsigned char B;
	unsigned char G;
	unsigned char R;

// �室�� ��ࠬ����: N - ��� 梥� �����'a-06�.
// ��室�� ��ࠬ����: R, G, B - ��� 梥� ��� BMP-䠩��.

void GetRGB(unsigned char N)
{
	unsigned char array_bit[8]; // ���ᨢ � ��ᥬ�� ��⠬�.
	unsigned char addr; // ���� ��� array_bit.

	// ���� �����-06� �१ 梥� PC ��������.
	// ���ᨢ� 梥⮢.
	unsigned char array_PC_R[8] = { 0, 36, 72, 108, 144, 180, 216, 255 }; // 3 ��� ����.
	unsigned char array_PC_G[8] = { 0, 36, 72, 108, 144, 180, 216, 255 }; // 3 ��� �����.
	unsigned char array_PC_B[4] = { 0, 85, 170, 255 }; // 2 ��� ᨭ��.

	addr = 0;

	// N � ����筮� �᫮.
	while (N) // ���� �� ���稫��� ����.
		{
		array_bit[addr++] = N % 2;
		N = N / 2;                           //
		}                                    // �ਬ�砭��.
                                                     //   ---
	// ��⠢襩�� ���ᨢ ��������� ��ﬨ.       //   | ������: array_bit[addr++];
	for (addr = addr; addr < 8;)                 //   ---
		{                                    //   ---
		array_bit[addr] = 0;                 //   | ��������筠: array_bit[addr];
		addr++;                              //   |              addr++;
		}                                    //   ---
                                                     //
	// Blue. 2 ��� ᨭ��.
	if (array_bit[7] == 0 && array_bit[6] == 0) // 0.
		{
		B = array_PC_B[0];
		goto M1;
		}
	if (array_bit[7] == 0 && array_bit[6] == 1) // 1.
		{
		B = array_PC_B[1];
		goto M1;
		}
	if (array_bit[7] == 1 && array_bit[6] == 0) // 2.
		{
		B = array_PC_B[2];
		goto M1;
		}
	if (array_bit[7] == 1 && array_bit[6] == 1) // 3.
		{
		B = array_PC_B[3];
		}

M1:

	// Green. 3 ��� �����.
	if (array_bit[5] == 0 && array_bit[4] == 0 && array_bit[3] == 0) // 0.
		{
		G = array_PC_G[0];
		goto M2;
		}
	if (array_bit[5] == 0 && array_bit[4] == 0 && array_bit[3] == 1) // 1.
		{
		G = array_PC_G[1];
		goto M2;
		}
	if (array_bit[5] == 0 && array_bit[4] == 1 && array_bit[3] == 0) // 2.
		{
		G = array_PC_G[2];
		goto M2;
		}
	if (array_bit[5] == 0 && array_bit[4] == 1 && array_bit[3] == 1) // 3.
		{
		G = array_PC_G[3];
		goto M2;
		}
	if (array_bit[5] == 1 && array_bit[4] == 0 && array_bit[3] == 0) // 4.
		{
		G = array_PC_G[4];
		goto M2;
		}
	if (array_bit[5] == 1 && array_bit[4] == 0 && array_bit[3] == 1) // 5.
		{
		G = array_PC_G[5];
		goto M2;
		}
	if (array_bit[5] == 1 && array_bit[4] == 1 && array_bit[3] == 0) // 6.
		{
		G = array_PC_G[6];
		goto M2;
		}
	if (array_bit[5] == 1 && array_bit[4] == 1 && array_bit[3] == 1) // 7.
		{
		G = array_PC_G[7];
		}

M2:

	// Red. 3 ��� ����.
	if (array_bit[2] == 0 && array_bit[1] == 0 && array_bit[0] == 0) // 0.
		{
		R = array_PC_R[0];
		goto M3;
		}
	if (array_bit[2] == 0 && array_bit[1] == 0 && array_bit[0] == 1) // 1.
		{
		R = array_PC_R[1];
		goto M3;
		}
	if (array_bit[2] == 0 && array_bit[1] == 1 && array_bit[0] == 0) // 2.
		{
		R = array_PC_R[2];
		goto M3;
		}
	if (array_bit[2] == 0 && array_bit[1] == 1 && array_bit[0] == 1) // 3.
		{
		R = array_PC_R[3];
		goto M3;
		}
	if (array_bit[2] == 1 && array_bit[1] == 0 && array_bit[0] == 0) // 4.
		{
		R = array_PC_R[4];
		goto M3;
		}
	if (array_bit[2] == 1 && array_bit[1] == 0 && array_bit[0] == 1) // 5.
		{
		R = array_PC_R[5];
		goto M3;
		}
	if (array_bit[2] == 1 && array_bit[1] == 1 && array_bit[0] == 0) // 6.
		{
		R = array_PC_R[6];
		goto M3;
		}
	if (array_bit[2] == 1 && array_bit[1] == 1 && array_bit[0] == 1) // 7.
		{
		R = array_PC_R[7];
		}

M3:

	return;
}
