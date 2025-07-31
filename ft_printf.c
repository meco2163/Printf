/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:02:43 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/31 14:52:34 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_bonus_format(const char *ptr)
{
	while (*ptr && (*ptr == '-' || *ptr == '0' || *ptr == '+' || *ptr == ' '
			|| *ptr == '#' || (*ptr >= '0' && *ptr <= '9') || *ptr == '.'))
		ptr++;
	if (*ptr == 'c' || *ptr == 's' || *ptr == 'd' || *ptr == 'i' || *ptr == 'u'
		|| *ptr == 'x' || *ptr == 'X' || *ptr == 'p' || *ptr == '%')
		return (1);
	return (0);
}

static int	handle_conversion_mandatory(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	if (c == 's')
		return (ft_print_string(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(args, int)));
	if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_print_hex_lower(va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_print_hex_upper(va_arg(args, unsigned int)));
	if (c == 'p')
		return (ft_print_pointer(va_arg(args, unsigned long)));
	if (c == '%')
		return (ft_print_percent());
	return (write(1, &c, 1));
}

static int	handle_conversion_bonus_core(char c, va_list args, t_flags *flags)
{
	if (c == 'c')
		return (ft_print_char_bonus(va_arg(args, int), flags));
	if (c == 's')
		return (ft_print_string_bonus(va_arg(args, char *), flags));
	if (c == 'd' || c == 'i')
		return (ft_print_int_bonus(va_arg(args, int), flags));
	if (c == 'u')
		return (ft_print_unsigned_bonus(flags, args));
	if (c == 'x' || c == 'X' || c == 'p')
		return (ft_print_hex_bonus(flags, args, c));
	if (c == '%')
		return (ft_print_percent_bonus(flags));
	return (write(1, &c, 1));
}

static int	process_format(const char **format, va_list args)
{
	const char	*ptr;
	t_flags		flags;

	ptr = *format + 1;
	if (is_bonus_format(ptr) && (*ptr == '-' || *ptr == '0' || *ptr == '+'
			|| *ptr == ' ' || *ptr == '#' || (*ptr >= '0' && *ptr <= '9')
			|| *ptr == '.'))
	{
		(*format)++;
		parse_all_flags(format, &flags, args);
		return (handle_conversion_bonus_core(**format, args, &flags));
	}
	(*format)++;
	return (handle_conversion_mandatory(**format, args));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			count += process_format(&format, args);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
