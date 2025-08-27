/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:24 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 02:55:12 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	precheck_format(const char *s)
{
	const char	*q;
	int			ok;

	while (*s)
	{
		if (*s != '%')
		{
			s++;
			continue ;
		}
		if (*(s + 1) == '\0')
			return (-1);
		ok = scan_meta(s + 1, &q);
		if (ok)
		{
			s = q + 1;
			continue ;
		}
		if (*q == '\0')
			return (-1);
		s = q;
	}
	return (0);
}

static int	handle_conversion_mandatory(char c, va_list args)
{
	int		count;
	char	ch;

	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	if (c == 's')
		return (ft_print_string(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(args, int)));
	if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X' || c == 'p')
		return (ft_print_hex(c, args));
	if (c == '%')
		return (ft_print_percent());
	ch = c;
	count = acc_write(1, &ch, 1);
	if (count < 0)
		return (-1);
	return (count);
}

static int	process_percent_mandatory(const char **format, va_list args)
{
	const char	*q;
	int			is_spec;

	is_spec = scan_meta(*format + 1, &q);
	if (is_spec)
	{
		*format = q + 1;
		return (handle_conversion_mandatory(*q, args));
	}
	return (emit_invalid_seq(format));
}

static int	step(const char **format, va_list args)
{
	int	part;

	if (**format != '%')
	{
		part = acc_write(1, *format, 1);
		if (part < 0)
			return (-1);
		(*format)++;
		return (part);
	}
	if (*(*format + 1) == '\0')
		return (-1);
	return (process_percent_mandatory(format, args));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		part;

	if (!format)
		return (-1);
	if (precheck_format(format) < 0)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		part = step(&format, args);
		if (part < 0)
		{
			va_end(args);
			return (-1);
		}
		count += part;
	}
	va_end(args);
	return (count);
}
