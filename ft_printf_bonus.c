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
	return (write(1, "%", 1));
}

static int	process_percent(const char **fmt, va_list args, t_flags *flags)
{
	int	n;

	if (**fmt == '\0')
		return (write(1, "%", 1));
	parse_all_flags(fmt, flags, args);
	if (**fmt == '\0')
		return (write(1, "%", 1));
	if (**fmt == '%')
	{
		(*fmt)++;
		return (ft_print_percent_bonus(flags));
	}
	if (**fmt == 'c' || **fmt == 's' || **fmt == 'd' || **fmt == 'i'
		|| **fmt == 'u' || **fmt == 'x' || **fmt == 'X' || **fmt == 'p')
	{
		n = handle_conversion_bonus(**fmt, args, flags);
		(*fmt)++;
		return (n);
	}
	n = write(1, "%", 1);
	(*fmt)++;
	return (n);
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
