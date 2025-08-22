/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:38:33 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 01:10:34 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_precision_padding(int width)
{
	int	part;

	part = put_padding(width, '0');
	if (part < 0)
		return (-1);
	return (part);
}

static int	print_sign(int n, t_flags *flags)
{
	int		count;
	char	ch;

	count = 0;
	if (n < 0)
		ch = '-';
	else if (flags->plus)
		ch = '+';
	else if (flags->space)
		ch = ' ';
	else
		return (0);
	if (acc_write(&count, &ch, 1) < 0)
		return (-1);
	return (count);
}

static int	pre_left_no_minus(t_num_data *d, t_flags *f,
			t_hex_params *p, int *cnt)
{
	if (f->zero && f->dot < 0)
	{
		p->part = print_sign(d->n, f);
		if (p->part < 0)
			return (-1);
		*cnt += p->part;
	}
	p->part = write_left_pad(f, p);
	if (p->part < 0)
		return (-1);
	*cnt += p->part;
	if (!(f->zero && f->dot < 0))
	{
		p->part = print_sign(d->n, f);
		if (p->part < 0)
			return (-1);
		*cnt += p->part;
	}
	return (0);
}

int	pre_left_stage(t_num_data *d, t_flags *f,
			t_hex_params *p, int *cnt)
{
	if (!f->minus)
		return (pre_left_no_minus(d, f, p, cnt));
	p->part = print_sign(d->n, f);
	if (p->part < 0)
		return (-1);
	*cnt += p->part;
	return (0);
}

int	body_and_tail(t_flags *f, t_hex_params *p,
			t_num_data *d, int *cnt)
{
	p->part = print_precision_padding(p->dotpad);
	if (p->part < 0)
		return (-1);
	*cnt += p->part;
	p->part = ft_putnstr_fd(d->num_str, p->len, 1);
	if (p->part < 0)
		return (-1);
	*cnt += p->part;
	if (f->minus)
	{
		p->part = write_right_pad(f, p);
		if (p->part < 0)
			return (-1);
		*cnt += p->part;
	}
	return (0);
}
