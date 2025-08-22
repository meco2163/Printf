/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:00 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 03:48:22 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
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

static int	emit_left_side(unsigned long n, t_flags *f, char format,
			t_hex_params *params)
{
	int	zero_mode;
	int	count;
	int	part;

	zero_mode = (f->zero && f->dot < 0 && !f->minus);
	count = 0;
	if (zero_mode)
		part = print_prefix_x(f, n, format);
	if (part < 0)
		return (-1);
	count += part;
	part = write_hex_left_pad(f, params, zero_mode);
	if (part < 0)
		return (-1);
	count += part;
	if (!zero_mode)
		part = print_prefix_x(f, n, format);
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

static int	emit_right_side(const char *s, t_flags *flags, t_hex_params *params)
{
	int	count;
	int	part;

	count = 0;
	part = put_padding(params->dotpad, '0');
	if (part < 0)
		return (-1);
	count += part;
	part = ft_putnstr_fd(s, params->len, 1);
	if (part < 0)
		return (-1);
	count += part;
	if (flags->minus)
	{
		part = put_padding(params->pad, ' ');
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

static int	print_hex_core(unsigned long n, const char *s,
			t_flags *flags, char format)
{
	t_hex_params	*params;
	int				count;
	int				part;

	params = compute_hex_params(s, flags, n, format);
	count = 0;
	part = emit_left_side(n, flags, format, &params);
	if (part < 0)
		return (-1);
	count += part;
	part = emit_right_side(s, flags, &params);
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

	n = (unsigned int)va_arg(args, unsigned int);
	if (is_zero_case(flags, n))
		return (write_padded_literal(NULL, 0, flags));
	s = ft_ultoa_base(n, format == 'X');
	if (!s)
		return (-1);
	count = print_hex_core(n, s, flags, format);
	free(s);
	return (count);
}
