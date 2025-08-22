/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:52:16 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 02:07:31 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static t_hex_params	ptr_params(const char *s, t_flags *flags)
{
	t_hex_params	p;
	int				total;

	p.len = (int)ft_strlen(s);
	p.dotpad = 0;
	if (flags->dot > p.len)
		p.dotpad = flags->dot - p.len;
	p.prefix_len = 2;
	total = p.prefix_len + p.dotpad + p.len;
	p.pad = flags->width - total;
	if (p.pad < 0)
		p.pad = 0;
	p.part = 0;
	return (p);
}

static int	emit_ptr_left(t_flags *f, t_hex_params *p, int zero_mode)
{
	int	count;

	count = 0;
	if (zero_mode)
	{
		if (acc_write(&count, "0x", 2) < 0)
			return (-1);
	}
	p->part = write_hex_left_pad(f, p, zero_mode);
	if (p->part < 0)
		return (-1);
	count += p->part;
	if (!zero_mode)
	{
		if (acc_write(&count, "0x", 2) < 0)
			return (-1);
	}
	return (count);
}

static int	ptr_body_tail(const char *s, t_flags *f, t_hex_params *p)
{
	int	count;

	count = 0;
	p->part = put_padding(p->dotpad, '0');
	if (p->part < 0)
		return (-1);
	count += p->part;
	p->part = ft_putnstr_fd(s, p->len, 1);
	if (p->part < 0)
		return (-1);
	count += p->part;
	if (f->minus)
	{
		p->part = put_padding(p->pad, ' ');
		if (p->part < 0)
			return (-1);
		count += p->part;
	}
	return (count);
}

static int	print_ptr_core(const char *s, t_flags *f)
{
	t_hex_params	p;
	int				count;
	int				zero_mode;

	p = ptr_params(s, f);
	zero_mode = (f->zero && f->dot < 0 && !f->minus);
	count = emit_ptr_left(f, &p, zero_mode);
	if (count < 0)
		return (-1);
	p.part = ptr_body_tail(s, f, &p);
	if (p.part < 0)
		return (-1);
	count += p.part;
	return (count);
}

int	ft_print_pointer_bonus(t_flags *flags, va_list args)
{
	unsigned long	ptr;
	t_hex_params	tmp;
	char			*s;
	int				count;

	ptr = (unsigned long)va_arg(args, void *);
	if (ptr == 0)
	{
		tmp.len = 5;
		tmp.pad = 0;
		tmp.part = 0;
		return (write_padded_literal(flags, &tmp, "(nil)"));
	}
	s = ft_ultoa_base(ptr, 0);
	if (!s)
		return (-1);
	count = print_ptr_core(s, flags);
	free(s);
	return (count);
}
