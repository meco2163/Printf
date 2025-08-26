/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:38:02 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 16:28:51 by mekaplan         ###   ########.fr       */
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

static void	init_calc(t_hex_params *params, t_num_data *d, t_flags *f)
{
	int	total;

	params->len = d->num_len;
	params->dotpad = d->precision_padding;
	params->prefix_len = 0;
	total = d->num_len + d->precision_padding;
	if (d->n < 0 || f->plus || f->space)
		total++;
	params->pad = get_padding(f->width, total);
	params->part = 0;
}

static int	print_number_with_flags(t_num_data *data, t_flags *flags)
{
	t_hex_params	params;
	int				count;
	int				part;

	init_calc(&params, data, flags);
	count = 0;
	part = pre_left_stage(data, flags, &params);
	if (part < 0)
		return (-1);
	count += part;
	part = body_and_tail(flags, &params, data);
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

static int	prepare_num_data(int n, t_flags *flags, t_num_data *data)
{
	int		precision_padding;
	char	*num_str;
	int		num_len;

	precision_padding = 0;
	num_str = create_num_str(n, flags);
	if (!num_str)
		return (-1);
	num_len = ft_strlen(num_str);
	if (flags->dot >= 0 && flags->dot > num_len)
		precision_padding = flags->dot - num_len;
	data->n = n;
	data->num_str = num_str;
	data->num_len = num_len;
	data->precision_padding = precision_padding;
	return (0);
}

int	ft_print_int_bonus(int n, t_flags *flags)
{
	t_num_data	data;
	int			count;

	if (prepare_num_data(n, flags, &data) < 0)
		return (-1);
	count = print_number_with_flags(&data, flags);
	free(data.num_str);
	return (count);
}
