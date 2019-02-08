
    Написано на Си в FreeBSD!

    grf2bmp.c        - Гланый файл.
    CodeConversion.c - Перекодировка цвета.
    GetRGB.c         - Цвета Вектор-06Ц через цвета PC компьютера.
    LoadGRF.c        - Загрузить GRF файл в память.
    SaveBMP.c        - Сохранить BMP файл на диск.
    UnpackingGRF.c   - Распаковать GRF файл.

    CodeConversion.o - Объектные файлы.
    GetRGB.o         - -/-
    LoadGRF.o        - -/-
    SaveBMP.o        - -/-
    grf2bmp.o        - -/-
    UnpackingGRF.o   - -/-

    obj.sh      - Чтобы не делать объектные файлы руками.
    linking.sh  - Чтобы не делать линковку руками.

    Readme-SRC.RUS.1251.txt - Это описание в кодировке cp1251 (Windows).
    Readme-SRC.RUS.UTF8.txt - Это описание в кодировке UTF-8 (FreeBSD, Linux).

    Как скомпилировать исполняемый файл в FreeBSD или Linux!
 
       Действие 1. Создаём объектные файлы.
       $ gcc -c grf2bmp.c LoadGRF.c UnpackingGRF.c CodeConversion.c GetRGB.c SaveBMP.c

       Действие 2. Линковка объектных файлов.
       $ gcc grf2bmp.o LoadGRF.o UnpackingGRF.o CodeConversion.o GetRGB.o SaveBMP.o -o grf2bmp

       На выходе исполняемый файл grf2bmp

    Как скомпилировать исполняемый файл в FreeBSD или Linux для Windows!

       Действие 1. Создаём объектные файлы.
       $ mingw32-gcc -c grf2bmp.c LoadGRF.c UnpackingGRF.c CodeConversion.c GetRGB.c SaveBMP.c

       Действие 2. Линковка объектных файлов.
       $ mingw32-gcc grf2bmp.o LoadGRF.o UnpackingGRF.o CodeConversion.o GetRGB.o SaveBMP.o -o grf2bmp.exe

       На выходе исполняемый файл grf2bmp.exe

    ---
    | Каталог Perl - для получения заголовка bmp файлы.
    ---

    Примечание.
    Каталог Perl в "SRC - Windows" - отсутствует.

    ---
    | Каталог Test - Тестовые изображения.
    ---

    Ukraine. (C) Демидов С.В.
