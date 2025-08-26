/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:52:16 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 22:36:15 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static t_hex_params	ptr_params(const char *s, t_flags *flags)
{
	t_hex_params	params;
	int				total;

	params.len = (int)ft_strlen(s);
	params.dotpad = 0;
	if (flags->dot > params.len)
		params.dotpad = flags->dot - params.len;
	params.prefix_len = 2;
	total = params.prefix_len + params.dotpad + params.len;
	params.pad = flags->width - total;
	if (params.pad < 0)
		params.pad = 0;
	params.part = 0;
	return (params);
}

static int	emit_ptr_left(t_flags *f, t_hex_params *params, int zero_mode)
{
	int	count;
	int	part;

	count = 0;
	if (zero_mode)
	{
		part = acc_write(1, "0x", 2);
		if (part < 0)
			return (-1);
		count += part;
	}
	part = write_hex_left_pad(f, params, zero_mode);
	if (part < 0)
		return (-1);
	count += part;
	if (!zero_mode)
	{
		part = acc_write(1, "0x", 2);
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

static int	ptr_body_tail(const char *s, t_flags *f, t_hex_params *params)
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
	if (f->minus)
	{
		part = put_padding(params->pad, ' ');
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

static int	print_ptr_core(const char *s, t_flags *f)
{
	t_hex_params	params;
	int				count;
	int				part;
	int				zero_mode;

	params = ptr_params(s, f);
	zero_mode = (f->zero && f->dot < 0 && !f->minus);
	count = 0;
	part = emit_ptr_left(f, &params, zero_mode);
	if (part < 0)
		return (-1);
	count += part;
	part = ptr_body_tail(s, f, &params);
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

int	ft_print_pointer_bonus(t_flags *flags, va_list args)
{
	unsigned long	ptr;
	t_hex_params	params;
	char			*s;
	int				count;

	ptr = (unsigned long)va_arg(args, void *);
	if (ptr == 0)
	{
		params.len = 5;
		params.dotpad = 0;
		params.prefix_len = 0;
		params.pad = 0;
		params.part = 0;
		return (write_padded_literal(flags, &params, "(nil)", 0));
	}
	s = ft_ultoa_base(ptr, 0);
	if (!s)
		return (-1);
	count = print_ptr_core(s, flags);
	free(s);
	return (count);
}
