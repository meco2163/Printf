/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:08 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 02:31:34 by mekaplan         ###   ########.fr       */
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

static int	guard_trailing_percent(const char **format)
{
	int	count;

	if (**format != '\0')
		return (0);
	count = acc_write(1, "%", 1);
	if (count < 0)
		return (-1);
	return (-1);
}

static int	process_percent_bonus(const char **format, va_list args,
			t_flags *flags)
{
	const char	*start;
	int			r;
	int			count;

	r = guard_trailing_percent(format);
	if (r < 0)
		return (-1);
	start = *format;
	parse_all_flags(format, flags, args);
	r = guard_trailing_percent(format);
	if (r < 0)
		return (-1);
	if (is_spec((int)**format))
	{
		count = handle_conversion_bonus(**format, args, flags);
		(*format)++;
		return (count);
	}
	return (emit_invalid_seq_bonus(format, start));
}

static int	step_bonus(const char **format, va_list args,
			t_flags *flags, int *count)
{
	int	part;

	if (**format != '%')
	{
		part = acc_write(1, *format, 1);
		if (part < 0)
			return (-1);
		*count += part;
		(*format)++;
		return (0);
	}
	(*format)++;
	part = process_percent_bonus(format, args, flags);
	if (part < 0)
		return (-1);
	*count += part;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;
	int		status;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		status = step_bonus(&format, args, &flags, &count);
		if (status)
		{
			va_end(args);
			return (-1);
		}
	}
	va_end(args);
	return (count);
}
