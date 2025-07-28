#include "ft_printf_bonus.h"

static int	get_print_len(const char *str, t_flags *flags)
{
	int	len;

	len = ft_strlen(str);
	if (flags->dot && flags->precision < len && flags->precision >= 0)
		return (flags->precision);
	return (len);
}

static int	get_padding(int width, int print_len)
{
	if (width > print_len)
		return (width - print_len);
	return (0);
}

int	ft_print_string_bonus(const char *str, t_flags *flags)
{
	int	print_len;
	int	padding;

	if (!str)
		str = "(null)";
	print_len = get_print_len(str, flags);
	padding = get_padding(flags->width, print_len);
	if (!flags->minus)
		put_padding(padding, ' ');
	ft_putstrn((char *)str, print_len);
	if (flags->minus)
		put_padding(padding, ' ');
	return (print_len + padding);
}
