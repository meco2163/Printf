/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:34:49 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 16:49:38 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->dot = -1;
	flags->width = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
}

static void	parse_flags(const char **format, t_flags *flags)
{
	while (**format == '-' || **format == '0' || **format == '#'
		|| **format == ' ' || **format == '+')
	{
		if (**format == '-')
			flags->minus = 1;
		else if (**format == '0')
			flags->zero = 1;
		else if (**format == '#')
			flags->hash = 1;
		else if (**format == ' ')
			flags->space = 1;
		else if (**format == '+')
			flags->plus = 1;
		(*format)++;
	}
}

static void	parse_width(const char **format, t_flags *flags, va_list args)
{
	flags->width = 0;
	if (**format == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->minus = 1;
			flags->width = -flags->width;
		}
		(*format)++;
	}
	else
	{
		while (**format >= '0' && **format <= '9')
		{
			flags->width = flags->width * 10 + (**format - '0');
			(*format)++;
		}
	}
}

static void	parse_precision(const char **format, t_flags *flags, va_list args)
{
	flags->dot = -1;
	if (**format == '.')
	{
		flags->dot = 0;
		(*format)++;
		if (**format == '*')
		{
			flags->dot = va_arg(args, int);
			(*format)++;
		}
		else
		{
			while (**format >= '0' && **format <= '9')
			{
				flags->dot = flags->dot * 10 + (**format - '0');
				(*format)++;
			}
		}
		if (flags->dot < 0)
			flags->dot = -1;
	}
}

int	parse_all_flags(const char **format, t_flags *flags, va_list args)
{
	init_flags(flags);
	parse_flags(format, flags);
	parse_width(format, flags, args);
	parse_precision(format, flags, args);
	if (flags->minus)
		flags->zero = 0;
	if (flags->plus)
		flags->space = 0;
	return (0);
}
