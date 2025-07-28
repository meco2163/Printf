#include "ft_printf_bonus.h"
#include <unistd.h>

int print_char_bonus(char c, t_flags *flags)
{
	int printed;
	int padding;

	printed = 0;
	padding = 0;
	if (flags->width > 1)
		padding = flags->width - 1;
	if (flags->minus == 0)
	{
		if (flags->zero)
			printed += put_padding(padding, '0');
		else
			printed += put_padding(padding, ' ');
	}
	write(1, &c, 1);
	printed++;
	if (flags->minus == 1)
		printed += put_padding(padding, ' ');
	return (printed);
}