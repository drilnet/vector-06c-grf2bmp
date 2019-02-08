
# Perl.
# Конвертер графических файлов (GRF в BMP).
# Ukraine. (C) Демидов С.В.';

	# Для объявления переменных.
	use strict;

	# В случае возникновений каких-либо проблем нужно остановить работу скрипта.
	use warnings FATAL => 'all';

	my $filename_GRF; # Здесь имя GRF файла.
	my $size_GRF; # Размер GRF файла.

	my @array_color_GRF; # Массив цветов (16 байт) GRF файла.
	my @array_data_GRF;  # Массив с данными GRF.

	# Распаковка GRF данных.
	# ---
	my $addr_VCS; # Адрес для экранной области Вектора (в массиве).
	my $addr_GRF; # Адрес для данныx GRF (в массиве).

	my $bit_s;      # 1 - повторяющиеся байты, 0 - не повторяющиеся байты.
	my $count_byte; # Счётчик для повторяющихся байт и не для поворяющихся.
	my $total_byte; # Сколько повторяющихся байт и сколько не повторяющихся байт.

	# Экранная область Вектор-06Ц.
	# Здесь распакованные данные.
	my @array_screen_area_8000_FFFF;

	# Вывод цветов GRF файла на экран.
	# ---
	my $count_color; # Счётчик для цветов.

	# Перекодировка цвета.
	# ---
	my $addr_screen_8000_9FFF; # Адрес экранной области Вектор-06Ц.
	my $addr_screen_A000_BFFF; # -/-
	my $addr_screen_C000_DFFF; # -/-
	my $addr_screen_E000_FFFF; # -/-

	my $bit8_8000_9FFF; # 8 бит из экранной области Вектор-06Ц.
	my $bit8_A000_BFFF; # -/-
	my $bit8_C000_DFFF; # -/-
	my $bit8_E000_FFFF; # -/-

	my $z;
	my $y;
	my $x;

	my $addr_bmp; # Адрес в массиве @array_data_bmp_hex;

	# Запись BMP файла.
	# ---
	my $title_bmp_hex;   # Заголовок bmp файла.
	my $file_bmp_length; # Длина (размер) bmp файла.
	my $filename_BMP;    # Здесь имя BMP файла.

	# ---

	my @array_bit8_8000_9FFF; # Массив с восемью битами (перекодировка цвета).
	my @array_bit8_A000_BFFF; # -/-
	my @array_bit8_C000_DFFF; # -/-
	my @array_bit8_E000_FFFF; # -/-

	my @array_data_bmp_hex; # Массив с данными (данные bmp файла).

	#
	# ---
	my $temp; # Временный результат.

	if (defined $ARGV[0] != 1) # Если неинициализирован @ARGV, значит, пусто.
		{
		$ARGV[0] = '';
		}

	if (defined $ARGV[1] != 1) # Если неинициализирован @ARGV, значит, пусто.
		{
		$ARGV[1] = '';
		}

	$filename_GRF = $ARGV[0];

	if ($ARGV[0] eq '')
	{

	print "\n";
	print 'Конвертер графических файлов (GRF в BMP).';
	print "\n";
	print '   Ukraine. (C) Демидов С.В.';
	print "\n";
	print "\n";
	print '   GRF - графический формат файлов Вектор\'а-06Ц.';
	print "\n";
	print '   BMP - графический формат файлов Windows.';
	print "\n";
	print "\n";
	print '   Формат командной строки:';
	print "\n";
	print '      $ perl grf2bmp.pl имя_файла.grf';
	print "\n";
	print "\n";

	}
	else
	{

	print "\n";

# ---

	print '             Файл: ';
	print $filename_GRF;
	print "\n";

# ---

	# Получить размер GRF файла.
	$size_GRF = -s "$filename_GRF";

	print ' Размер GRF файла: ' . $size_GRF . ' байт.';
	print "\n";

	# Чтение GRF файла.
	open (InFileBin, "<" . $filename_GRF) or die "Ошибка...";
		sysread(InFileBin, $temp, $size_GRF, 0);
			close (InFileBin);

	$temp = unpack('H' . $size_GRF * 2, $temp);

	@array_color_GRF = unpack("(a2)*", substr($temp, 0, 16*2));
	@array_data_GRF = unpack("(a2)*", substr($temp, 16*2));

	# Палитру в Dec.
	for ($z=0; $z < @array_color_GRF;)
		{
		$array_color_GRF[$z] = hex $array_color_GRF[$z];
		$z++;
		}

	# GRF данные в Dec.
	for ($z=0; $z < @array_data_GRF;)
		{
		$array_data_GRF[$z] = hex $array_data_GRF[$z];
		$z++;
		}

# ---

	print 'Размер GRF данных: ' . scalar(@array_data_GRF) . ' байт (минус цвета, но плюс мусор).';
	print "\n";

# ---

	# Вывод цветов.

	print '  Цвета GRF файла: ';

	for ($count_color = 0; $count_color < 16;)
		{
		print sprintf("%02X", $array_color_GRF[$count_color]) . 'H';
		if ($count_color != 15)
			{
			print ' ';
			}

		$count_color++;
		}

	print'.';
	print "\n";

# ---

	# ---
	# | Распаковка GRF данных.
	# ---

	$addr_VCS = 0;

	# Распаковка.
	for ($addr_GRF = 0; $addr_GRF < @array_data_GRF; $addr_GRF++)
		{

		# Если встретился 0, значит прервать цикл (конец распаковки).
		if ($array_data_GRF[$addr_GRF] == 0)
			{
			last;
			}

		$bit_s = substr(sprintf("%08b", $array_data_GRF[$addr_GRF]), 0, 1);

		if ($bit_s eq '1')
			{
			# Не повторяющиеся байты.
			# ---

			$total_byte = $array_data_GRF[$addr_GRF];
			$total_byte = 127 & $total_byte; # 7F и $total_byte.

			for ($count_byte = 0; $count_byte < $total_byte;)
				{
				$addr_GRF++;

				if ($addr_VCS == 32768)
					{
					print "\n";
					print 'Ошибка GRF файла!';
					print "\n";
					print "\n";

					# Завершение.
					exit;
					}

				$array_screen_area_8000_FFFF[$addr_VCS] = $array_data_GRF[$addr_GRF];

				$addr_VCS++;

				$count_byte++;
				}

			}
			else
			{
			# Повторяющиеся байты.
			# ---

			$total_byte = $array_data_GRF[$addr_GRF];

			$addr_GRF++;

			for ($count_byte = 0; $count_byte < $total_byte;)
				{

				if ($addr_VCS == 32768)
					{
					print "\n";
					print 'Ошибка GRF файла!';
					print "\n";
					print "\n";

					# Завершение.
					exit;
					}

				$array_screen_area_8000_FFFF[$addr_VCS] = $array_data_GRF[$addr_GRF];

				$addr_VCS++;

				$count_byte++;
				}

			}

		}

	print '      Распаковано: ' . $addr_VCS . ' байт.';
	print "\n";

	if ($addr_VCS != 32768)
		{
		print "\n";
		print 'Ошибка GRF файла!';
		print "\n";
		print "\n";

		# Завершение.
		exit;
		}

# ---

	print 'Размер GRF данных: ';
	print $addr_GRF - 1 . ' байт (минус цвета, минус мусор).';
	print "\n";

# ---

	# Перекодировка цвета.

	$addr_screen_8000_9FFF = 0;
	$addr_screen_A000_BFFF = 8192;
	$addr_screen_C000_DFFF = 16384;
	$addr_screen_E000_FFFF = 24576;

	$addr_bmp = 0; # Левый нижний угол.

	for ($z = 0; $z < 32;)
		{

		my $push = $addr_bmp;

		for ($y=0; $y < 256;)
			{
			$bit8_8000_9FFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_8000_9FFF]);
			$bit8_A000_BFFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_A000_BFFF]);
			$bit8_C000_DFFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_C000_DFFF]);
			$bit8_E000_FFFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_E000_FFFF]);

			@array_bit8_8000_9FFF = split('', $bit8_8000_9FFF);
			@array_bit8_A000_BFFF = split('', $bit8_A000_BFFF);
			@array_bit8_C000_DFFF = split('', $bit8_C000_DFFF);
			@array_bit8_E000_FFFF = split('', $bit8_E000_FFFF);

			# Обрабатываем 4-ре байта.
			for ($x=0; $x < 8;)
				{
				if ($array_bit8_E000_FFFF[$x] eq '0' && # 0.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[0]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 1.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[1]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 2.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[2]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 3.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[3]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 4.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[4]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 5.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[5]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 6.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[6]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 7.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[7]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 8.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[8]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 9.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[9]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 10.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[10]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 11.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[11]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 12.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[12]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
						}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 13.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[13]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 14.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[14]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 15.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_GRF[15]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				$addr_bmp++;
				$x++;
				}

			$addr_bmp = $addr_bmp - 24 + 256 * 3;

			$addr_screen_8000_9FFF++;
			$addr_screen_A000_BFFF++;
			$addr_screen_C000_DFFF++;
			$addr_screen_E000_FFFF++;

			$y++;
			}

		$addr_bmp = $push;
		$addr_bmp = $addr_bmp + 24;

		$z++;
		}

# ---

	# Заголовок bmp файла.
	$title_bmp_hex = '424d7a000300000000007a0000006c00'; # 0000.
	$title_bmp_hex.= '00000001000000010000010018000000'; # 0010.
	$title_bmp_hex.= '000000000300130b0000130b00000000'; # 0020.
	$title_bmp_hex.= '00000000000042475273000000000000'; # 0030.
	$title_bmp_hex.= '00000000000000000000000000000000'; # 0040.
	$title_bmp_hex.= '00000000000000000000000000000000'; # 0050.
	$title_bmp_hex.= '00000000000000000000020000000000'; # 0060.
	$title_bmp_hex.= '00000000000000000000';             # 0070.

	$temp = $title_bmp_hex . join('', @array_data_bmp_hex);
	$file_bmp_length = length($temp) / 2;
	$temp = pack('H' . length($temp), $temp);

	print 'Размер BMP данных: ' . scalar(@array_data_bmp_hex) . '. ';
	print "\n";
	print ' Размер BMP файла: ' . $file_bmp_length . '. ';
	print "\n";

	$filename_BMP = substr($filename_GRF, 0, length($filename_GRF) - 3);
	$filename_BMP.= 'bmp';

	# Записать изображение (файл bmp).
	open (InFileBin, ">" . $filename_BMP) or die "Ошибка...";
		syswrite(InFileBin, $temp, $file_bmp_length, 0);
			close (InFileBin);

	print "\n";
	print '   OK!';
	print "\n";
	print "\n";

	}

# ----- ----- ----- ----- ----- ----- -----

#
# Цвета Вектор-06Ц через цвета PC компьютера.
#

sub getRGB
{
	my $countpalette; # Сяётчик для палитры.
	my $R_bit;   # Биты для R.
	my $G_bit;   # Биты для G.
	my $B_bit;   # Биты для B.
	my $R;       # Текущий цвет R.
	my $G;       # Текущий цвет G.
	my $B;       # Текущий цвет B.
	my $RGB_hex; # Текущий цвет RGB (hex).
	my $BGR_hex; # Текущий цвет RGB (hex) наоборот.

	# Массивы цветов Вектор-06Ц.
	my @array_PC_R; # Красный.
	my @array_PC_G; # Зелёный.
	my @array_PC_B; # Синий.

	# Массивы цветов Вектор-06Ц.
	@array_PC_R = (0, 36, 72, 108, 144, 180, 216, 255);
	@array_PC_G = (0, 36, 72, 108, 144, 180, 216, 255);
	@array_PC_B = (0, 85, 170, 255);


		# Получить палитру.
		$temp = $_[0];
		# В двоичную систему.
		$temp = sprintf('%b', $temp);
		# Дополнить нулями слева (если нужно).
		$temp = sprintf("%08d", $temp);

#		print $temp . ' - ';

		# 2 бита синий.
		$B_bit = substr($temp, 0, 2);
#		print $B_bit . ' ';

		# 3 бита зелёный.
		$G_bit = substr($temp, 2, 3);
#		print $G_bit . ' ';

		# 3 бита красный.
		$R_bit = substr($temp, 5, 3);
#		print $R_bit;

		# Blue.
		if ($B_bit eq '00')
			{
			$B = $array_PC_B[0];
			}
		if ($B_bit eq '01')
			{
			$B = $array_PC_B[1];
			}
		if ($B_bit eq '10')
			{
			$B = $array_PC_B[2];
			}
		if ($B_bit eq '11')
			{
			$B = $array_PC_B[3];
			}

		# Green.
		if ($G_bit eq '000')
			{
			$G = $array_PC_G[0];
			}
		if ($G_bit eq '001')
			{
			$G = $array_PC_G[1];
			}
		if ($G_bit eq '010')
			{
			$G = $array_PC_G[2];
			}
		if ($G_bit eq '011')
			{
			$G = $array_PC_G[3];
			}
		if ($G_bit eq '100')
			{
			$G = $array_PC_G[4];
			}
		if ($G_bit eq '101')
			{
			$G = $array_PC_G[5];
			}
		if ($G_bit eq '110')
			{
			$G = $array_PC_G[6];
			}
		if ($G_bit eq '111')
			{
			$G = $array_PC_G[7];
			}

		# Red.
		if ($R_bit eq '000')
			{
			$R = $array_PC_R[0];
			}
		if ($R_bit eq '001')
			{
			$R = $array_PC_R[1];
			}
		if ($R_bit eq '010')
			{
			$R = $array_PC_R[2];
			}
		if ($R_bit eq '011')
			{
			$R = $array_PC_R[3];
			}
		if ($R_bit eq '100')
			{
			$R = $array_PC_R[4];
			}
		if ($R_bit eq '101')
			{
			$R = $array_PC_R[5];
			}
		if ($R_bit eq '110')
			{
			$R = $array_PC_R[6];
			}
		if ($R_bit eq '111')
			{
			$R = $array_PC_R[7];
			}

#		$RGB_hex = sprintf("%02x", $R) . sprintf("%02x", $G) . sprintf("%02x", $B);
		$BGR_hex = sprintf("%02x", $B) . sprintf("%02x", $G) . sprintf("%02x", $R);

#		print ' - ';
#		print $RGB_hex;

		return $BGR_hex;
}