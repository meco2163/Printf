/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:08 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 02:57:29 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_conversion_bonus(char c, va_list args, t_flags *flags)
{
	int		count;
	char	ch;

	if (c == 'c')
		return (ft_print_char_bonus(va_arg(args, int), flags));
	if (c == 's')
		return (ft_print_string_bonus(va_arg(args, char *), flags));
	if (c == 'd' || c == 'i')
		return (ft_print_int_bonus(va_arg(args, int), flags));
	if (c == 'u')
		return (ft_print_unsigned_bonus(flags, args));
	if (c == 'x' || c == 'X')
		return (ft_print_hex_bonus(flags, args, c));
	if (c == 'p')
		return (ft_print_pointer_bonus(flags, args));
	if (c == '%')
		return (ft_print_percent_bonus(flags));
	ch = c;
	count = acc_write(1, &ch, 1);
	if (count < 0)
		return (-1);
	return (count);
}

static int	dispatch_after_flags(const char **format, va_list args,
			t_flags *flags, const char *start)
{
	int	count;

	if (**format == '%')
	{
		flags->hash = 0;
		flags->space = 0;
		flags->plus = 0;
		if (flags->dot >= 0)
			flags->dot = -1;
		count = ft_print_percent_bonus(flags);
		(*format)++;
		return (count);
	}
	if ((**format == 'c') || (**format == 's') || (**format == 'd')
		|| (**format == 'i') || (**format == 'u') || (**format == 'x')
		|| (**format == 'X') || (**format == 'p'))
	{
		count = handle_conversion_bonus(**format, args, flags);
		(*format)++;
		return (count);
	}
	return (emit_invalid_seq_bonus(format, start));
}

static int	process_percent_bonus(const char **format,
		va_list args, t_flags *flags)
{
	const char	*start;

	if (**format == '\0')
		return (-1);
	start = *format;
	parse_all_flags(format, flags, args);
	if (**format == '\0')
		return (-1);
	return (dispatch_after_flags(format, args, flags, start));
}

static int	step_bonus(const char **format, va_list args, t_flags *flags)
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
	(*format)++;
	part = process_percent_bonus(format, args, flags);
	if (part < 0)
		return (-1);
	return (part);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;
	int		part;

	if (!format)
		return (-1);
	if (precheck_format_bonus(format) < 0)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		part = step_bonus(&format, args, &flags);
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
