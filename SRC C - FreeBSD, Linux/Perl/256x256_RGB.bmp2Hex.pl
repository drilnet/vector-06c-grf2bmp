
# Perl5-5.26.2. Ukraine. (C) Demidov S.V.
# Пример вызова: $ perl 256x256_RGB_bmp2Hex.pl >256x256_RGB.bmp.hex

	# Для объявления переменных.
	use strict;

	# В случае возникновений каких-либо проблем нужно остановить работу скрипта.
	use warnings FATAL => 'all';

	# Объявление переменных.
	my $title_hex; # Заголовок bmp файла.
	my $temp;      # Временный результат.
	my $array;     # Адрес для массива @array_title_hex.
	my $array_2;   # Адрес для массива @array_title_hex_new.

	my $addr; # Адрес (с правой стороны).

	# Объявление массива.
	my @array_title_hex;
	my @array_title_hex_new;

	# Получаем заголовок с 0-7Ah = 0-122d.
	$title_hex = `hd -n 122 -v 256x256_RGB.bmp`;

	# Разделить по \n и поместить в массив
	@array_title_hex = split('\n', $title_hex);

	$addr = 0;
	for ($array = 0; $array < @array_title_hex - 1;)
		{
		# Отрезать адрес.
		$temp = substr($array_title_hex[$array], 10);
		# Отрезать ASCII.
		$temp = substr($temp, 0, 48);

		# Разрезать по пробелу и поместить в массив.
		@array_title_hex_new = split(' ', $temp);

		for ($array_2 = 0; $array_2 < @array_title_hex_new;)
			{
			print '0x' . $array_title_hex_new[$array_2] . ',';
			$array_2++;
			}

		print ' // ';

		# Добавляем адрес с правой стороны.
		print uc(sprintf("%04x", $addr)) . '.';

		print "\n";

		$addr = $addr + 16;
		$array++;
		}
