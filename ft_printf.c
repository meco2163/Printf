/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:24 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:11:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	handle_conversion_mandatory(char c, va_list args)
{
	int		count;
	char	ch;

	count = 0;
	if (c == 'c')
		count = ft_print_char(va_arg(args, int));
	else if (c == 's')
		count = ft_print_string(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count = ft_print_int(va_arg(args, int));
	else if (c == 'u')
		count = ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X' || c == 'p')
		count = ft_print_hex(c, args);
	else if (c == '%')
		count = ft_print_percent();
	else
	{
		ch = (char)c;
		if (acc_write(&count, &ch, 1) < 0)
			return (-1);
	}
	return (count);
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
	count = 0;
	if (acc_write(&count, "%", 1) < 0)
		return (-1);
	if (acc_write(&count, p, (int)(q - p)) < 0)
		return (-1);
	if (*q && !((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z')))
	{
		if (acc_write(&count, q, 1) < 0)
			return (-1);
		q++;
	}
	*format = q;
	return (count);
}

static int	process_percent_mandatory(const char **format, va_list args)
{
	char	next;
	int		count_part;

	next = *(*format + 1);
	if (is_spec((int)next))
	{
		*format += 2;
		count_part = handle_conversion_mandatory(next, args);
		return (count_part);
	}
	count_part = emit_invalid_seq(format);
	return (count_part);
}

static int	step(const char **format, va_list args, int *count)
{
	int	count_part;
	int	tmp;

	if (**format != '%')
		return (emit_literal(format, count));
	if (*(*format + 1) == '\0')
	{
		tmp = 0;
		if (acc_write(&tmp, "%", 1) < 0)
			return (-1);
		return (-2);
	}
	count_part = process_percent_mandatory(format, args);
	if (count_part < 0)
		return (-1);
	*count += count_part;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		status;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		status = step(&format, args, &count);
		if (status)
		{
			va_end(args);
			return (-1);
		}
	}
	va_end(args);
	return (count);
}
