/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:02:43 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/31 01:58:51 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_conversion(char c, va_list args, t_flags *flags)
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

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			parse_all_flags(&format, &flags, args);
			count += handle_conversion(*format, args, &flags);
			format++;
		}
		else
		{
			count += write(1, format, 1);
			format++;
		}
	}
	va_end(args);
	return (count);
}
