/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:24 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/19 13:24:50 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

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

static const char	*scan_meta_end(const char *p)
{
	while (*p && (*p == '-' || *p == '0' || *p == '#' || *p == ' '
			|| *p == '+' || *p == '*' || *p == '.'
			|| (*p >= '0' && *p <= '9')))
		p++;
	return (p);
}

static int	emit_invalid_seq(const char **format)
{
	const char	*p;
	const char	*q;
	int			count;

	p = *format + 1;
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

static int	process_percent_mandatory(const char **format, va_list args)
{
	char	next;

	if (*((*format) + 1) == '\0')
	{
		*format += 1;
		return (write(1, "%", 1));
	}
	next = *(*format + 1);
	if (next == 'c' || next == 's' || next == 'd' || next == 'i'
		|| next == 'u' || next == 'x' || next == 'X' || next == 'p'
		|| next == '%')
	{
		*format += 2;
		return (handle_conversion_mandatory(next, args));
	}
	return (emit_invalid_seq(format));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += process_percent_mandatory(&format, args);
			continue ;
		}
		count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
