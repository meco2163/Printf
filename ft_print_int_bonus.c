/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:38:02 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 01:13:08 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>
#include <limits.h>

static char	*create_num_str(int n, t_flags *flags)
{
	if (n == INT_MIN)
		return (ft_strdup("2147483648"));
	if (n == 0 && flags->dot == 0)
		return (ft_strdup(""));
	if (n < 0)
		return (ft_itoa(-n));
	return (ft_itoa(n));
}

static void	init_calc(t_hex_params *p, t_num_data *d, t_flags *f)
{
	int	total;

	p->len = d->num_len;
	p->dotpad = d->precision_padding;
	p->prefix_len = 0;
	total = d->num_len + d->precision_padding;
	if (d->n < 0 || f->plus || f->space)
		total++;
	p->pad = get_padding(f->width, total);
	p->part = 0;
}

static int	print_number_with_flags(t_num_data *data, t_flags *flags)
{
	t_hex_params	p;
	int				count;

	init_calc(&p, data, flags);
	count = 0;
	if (pre_left_stage(data, flags, &p, &count) < 0)
		return (-1);
	if (body_and_tail(flags, &p, data, &count) < 0)
		return (-1);
	return (count);
}

int	ft_print_int_bonus(int n, t_flags *flags)
{
	char		*num_str;
	int			num_len;
	int			precision_padding;
	int			count;
	t_num_data	data;

	precision_padding = 0;
	num_str = create_num_str(n, flags);
	if (!num_str)
		return (-1);
	num_len = ft_strlen(num_str);
	if (flags->dot >= 0 && flags->dot > num_len)
		precision_padding = flags->dot - num_len;
	data.n = n;
	data.num_str = num_str;
	data.num_len = num_len;
	data.precision_padding = precision_padding;
	count = print_number_with_flags(&data, flags);
	free(num_str);
	return (count);
}
