![](https://github.com/drilnet/vector-06c-grf2bmp/blob/master/UA.png)

Написано на Си в [FreeBSD](https://www.freebsd.org/ru/)!

**Исходники**:

    grf2bmp.c        - Гланый файл.
    CodeConversion.c - Перекодировка цвета.
    GetRGB.c         - Цвета Вектор-06Ц через цвета PC компьютера.
    LoadGRF.c        - Загрузить GRF файл в память.
    SaveBMP.c        - Сохранить BMP файл на диск.
    UnpackingGRF.c   - Распаковать GRF файл.

**Объектные файлы**:

    CodeConversion.o - Объектные файлы.
    GetRGB.o         - -/-
    LoadGRF.o        - -/-
    SaveBMP.o        - -/-
    grf2bmp.o        - -/-
    UnpackingGRF.o   - -/-

**Автоматизация процесса компиляции и сборки**:

    obj.sh      - Чтобы не делать объектные файлы руками.
    linking.sh  - Чтобы не делать линковку руками.

**Как скомпилировать исполняемый файл в FreeBSD или Linux!**
 
       Действие 1. Создаём объектные файлы.
       $ gcc -c grf2bmp.c LoadGRF.c UnpackingGRF.c CodeConversion.c GetRGB.c SaveBMP.c

       Действие 2. Линковка объектных файлов.
       $ gcc grf2bmp.o LoadGRF.o UnpackingGRF.o CodeConversion.o GetRGB.o SaveBMP.o -o grf2bmp

       На выходе исполняемый файл grf2bmp

**Как скомпилировать исполняемый файл в FreeBSD или Linux для Windows!**

       Действие 1. Создаём объектные файлы.
       $ mingw32-gcc -c grf2bmp.c LoadGRF.c UnpackingGRF.c CodeConversion.c GetRGB.c SaveBMP.c

       Действие 2. Линковка объектных файлов.
       $ mingw32-gcc grf2bmp.o LoadGRF.o UnpackingGRF.o CodeConversion.o GetRGB.o SaveBMP.o -o grf2bmp.exe

       На выходе исполняемый файл grf2bmp.exe

**Perl**:

    ---
    | Каталог Perl - для получения заголовка bmp файлы.
    ---

    Примечание.
    Каталог Perl в "SRC - Windows" - отсутствует.

**Тестовые изображения**:

    ---
    | Каталог Test
    ---

Ukraine. (C) Демидов С.В.
