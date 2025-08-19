/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:08 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/19 13:23:29 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	handle_conversion_bonus(char c, va_list args, t_flags *flags)
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

static const char	*scan_meta_end(const char *p)
{
	while (*p && (*p == '-' || *p == '0' || *p == '#' || *p == ' '
			|| *p == '+' || *p == '*' || *p == '.'
			|| (*p >= '0' && *p <= '9')))
		p++;
	return (p);
}

static int	emit_invalid_seq_bonus(const char **format, const char *start)
{
	const char	*p;
	const char	*q;
	int			count;

	p = start;
	q = scan_meta_end(p);
	if (*q == '\0')
	{
		*format = q;
		return (-1);
	}
	count = write(1, "%", 1);
	count += write(1, p, q - p);
	if (*q && !((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z')))
	{
		count += write(1, q, 1);
		q++;
	}
	*format = q;
	return (count);
}

static int	process_percent(const char **format, va_list args, t_flags *flags)
{
	const char	*start;
	int			count;

	if (**format == '\0')
		return (write(1, "%", 1));
	start = *format;
	parse_all_flags(format, flags, args);
	if (**format == '\0')
		return (write(1, "%", 1));
	if (**format == '%')
	{
		(*format)++;
		return (ft_print_percent_bonus(flags));
	}
	if (**format == 'c' || **format == 's' || **format == 'd'
		|| **format == 'i' || **format == 'u' || **format == 'x'
		|| **format == 'X' || **format == 'p')
	{
		count = handle_conversion_bonus(**format, args, flags);
		(*format)++;
		return (count);
	}
	return (emit_invalid_seq_bonus(format, start));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format != '%')
		{
			count += write(1, format, 1);
			format++;
		}
		else
		{
			format++;
			count += process_percent(&format, args, &flags);
		}
	}
	va_end(args);
	return (count);
}
