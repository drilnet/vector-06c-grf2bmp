
    �������� �� �� � FreeBSD!

    grf2bmp.c        - ������ ����.
    CodeConversion.c - ������������� �����.
    GetRGB.c         - ����� ������-06� ����� ����� PC ����������.
    LoadGRF.c        - ��������� GRF ���� � ������.
    SaveBMP.c        - ��������� BMP ���� �� ����.
    UnpackingGRF.c   - ����������� GRF ����.

    CodeConversion.o - ��������� �����.
    GetRGB.o         - -/-
    LoadGRF.o        - -/-
    SaveBMP.o        - -/-
    grf2bmp.o        - -/-
    UnpackingGRF.o   - -/-

    obj.sh      - ����� �� ������ ��������� ����� ������.
    linking.sh  - ����� �� ������ �������� ������.

    Readme-SRC.RUS.1251.txt - ��� �������� � ��������� cp1251 (Windows).
    Readme-SRC.RUS.UTF8.txt - ��� �������� � ��������� UTF-8 (FreeBSD, Linux).

    ��� �������������� ����������� ���� � FreeBSD ��� Linux!
 
       �������� 1. ������ ��������� �����.
       $ gcc -c grf2bmp.c LoadGRF.c UnpackingGRF.c CodeConversion.c GetRGB.c SaveBMP.c

       �������� 2. �������� ��������� ������.
       $ gcc grf2bmp.o LoadGRF.o UnpackingGRF.o CodeConversion.o GetRGB.o SaveBMP.o -o grf2bmp

       �� ������ ����������� ���� grf2bmp

    ��� �������������� ����������� ���� � FreeBSD ��� Linux ��� Windows!

       �������� 1. ������ ��������� �����.
       $ mingw32-gcc -c grf2bmp.c LoadGRF.c UnpackingGRF.c CodeConversion.c GetRGB.c SaveBMP.c

       �������� 2. �������� ��������� ������.
       $ mingw32-gcc grf2bmp.o LoadGRF.o UnpackingGRF.o CodeConversion.o GetRGB.o SaveBMP.o -o grf2bmp.exe

       �� ������ ����������� ���� grf2bmp.exe

    ---
    | ������� Perl - ��� ��������� ��������� bmp �����.
    ---

    ����������.
    ������� Perl � "SRC - Windows" - �����������.

    ---
    | ������� Test - �������� �����������.
    ---

    Ukraine. (C) ������� �.�.
