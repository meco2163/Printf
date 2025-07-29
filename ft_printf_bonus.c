/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:37:53 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 10:37:56 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	handle_conversion(char c, va_list args, t_flags *flags)
{
	if (c == 'c')
		return (ft_print_char_bonus(va_arg(args, int), flags));
	if (c == 's')
		return (ft_print_string_bonus(va_arg(args, char *), flags));
	if (c == 'd' || c == 'i')
		return (ft_print_int_bonus(va_arg(args, int), flags));
	if (c == 'u')
		return (ft_print_unsigned_bonus(va_arg(args, unsigned int), flags));
	if (c == 'x' || c == 'X')
		return (ft_print_hex_bonus(va_arg(args, unsigned int), flags, c));
	if (c == 'p')
		return (ft_print_pointer_bonus(va_arg(args, void *), flags));
	if (c == '%')
		return (ft_print_percent_bonus(flags));
	return (write(1, &c, 1));
}

int	ft_printf_bonus(const char *format, ...)
{
	va_list		args;
	t_flags		flags;
	int			printed;

	va_start(args, format);
	printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			parse_all_flags(&format, &flags, args);
			printed += handle_conversion(*format, args, &flags);
			format++;
		}
		else
		{
			printed += write(1, format, 1);
			format++;
		}
	}
	va_end(args);
	return (printed);
}
