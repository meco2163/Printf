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
	return (write(1, "%", 1));
}

static int	is_valid_mandatory(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X' || c == 'p' || c == '%')
		return (1);
	return (0);
}

static int	process_percent_mandatory(const char **fmt, va_list args)
{
	int		n;
	char	next;

	if (*((*fmt) + 1) == '\0')
	{
		n = write(1, "%", 1);
		*fmt += 1;
		return (n);
	}
	next = *(*fmt + 1);
	if (is_valid_mandatory(next))
	{
		n = handle_conversion_mandatory(next, args);
		*fmt += 2;
		return (n);
	}
	n = write(1, "%", 1);
	*fmt += 1;
	return (n);
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
