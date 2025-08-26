/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:00 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 17:07:57 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	print_prefix_x(t_flags *flags, unsigned long n, char format)
{
	int	count;
	int	part;

	count = 0;
	if (flags->hash && n != 0)
	{
		if (format == 'x')
			part = acc_write(1, "0x", 2);
		else
			part = acc_write(1, "0X", 2);
		if (part < 0)
			return (-1);
		count += part;
		return (count);
	}
	return (0);
}

static int	emit_prefix(t_flags *f, unsigned long n, char format)
{
	int	part;

	part = print_prefix_x(f, n, format);
	if (part < 0)
		return (-1);
	return (part);
}

static int	emit_left_side(
			unsigned long n, t_flags *f, char format, t_hex_params *p)
{
	int	zero_mode;
	int	count;
	int	part;

	zero_mode = (f->zero && f->dot < 0 && !f->minus);
	count = 0;
	if (zero_mode)
	{
		part = emit_prefix(f, n, format);
		if (add_count(&count, part) < 0)
			return (-1);
	}
	part = write_hex_left_pad(f, p, zero_mode);
	if (add_count(&count, part) < 0)
		return (-1);
	if (!zero_mode)
	{
		part = emit_prefix(f, n, format);
		if (add_count(&count, part) < 0)
			return (-1);
	}
	return (count);
}

static int	print_hex_core(
			unsigned long n, const char *s, t_flags *flags, char format)
{
	t_hex_params	p;
	int				count;
	int				part;

	p = compute_hex_params(s, flags, n, format);
	count = 0;
	part = emit_left_side(n, flags, format, &p);
	if (part < 0)
		return (-1);
	count += part;
	part = emit_right_side(s, flags, &p);
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

int	ft_print_hex_bonus(t_flags *flags, va_list args, char format)
{
	unsigned long	n;
	char			*s;
	int				count;
	t_hex_params	z;

	n = (unsigned int)va_arg(args, unsigned int);
	if (n == 0 && flags->dot == 0)
	{
		z.len = 0;
		z.dotpad = 0;
		z.prefix_len = 0;
		z.pad = 0;
		z.part = 0;
		return (write_padded_literal(flags, &z, "", 0));
	}
	s = ft_ultoa_base(n, format == 'X');
	if (!s)
		return (-1);
	count = print_hex_core(n, s, flags, format);
	free(s);
	return (count);
}
