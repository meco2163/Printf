/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:38:33 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 23:54:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_precision_padding(int width)
{
	int	part;

	part = put_padding(width, '0');
	if (part < 0)
		return (-1);
	return (part);
}

static int	print_sign(int n, t_flags *flags)
{
	int		part;
	char	ch;

	if (n < 0)
		ch = '-';
	else if (flags->plus)
		ch = '+';
	else if (flags->space)
		ch = ' ';
	else
		return (0);
	part = acc_write(1, &ch, 1);
	if (part < 0)
		return (-1);
	return (part);
}

static int	pre_left_no_minus(t_num_data *d, t_flags *f, t_hex_params *params)
{
	int	count;
	int	part;

	count = 0;
	if (f->zero && f->dot < 0)
	{
		part = print_sign(d->n, f);
		if (part < 0)
			return (-1);
		count += part;
	}
	part = write_left_pad(f, params);
	if (part < 0)
		return (-1);
	count += part;
	if (!(f->zero && f->dot < 0))
	{
		part = print_sign(d->n, f);
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

int	pre_left_stage(t_num_data *d, t_flags *f, t_hex_params *params)
{
	int	part;

	if (!f->minus)
		return (pre_left_no_minus(d, f, params));
	part = print_sign(d->n, f);
	if (part < 0)
		return (-1);
	return (part);
}

int	body_and_tail(t_flags *f, t_hex_params *params, t_num_data *d)
{
	int	count;
	int	part;

	count = 0;
	part = print_precision_padding(params->dotpad);
	if (part < 0)
		return (-1);
	count += part;
	part = ft_putnstr_fd(d->num_str, params->len, 1);
	if (part < 0)
		return (-1);
	count += part;
	if (f->minus)
	{
		part = write_right_pad(f, params);
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}
