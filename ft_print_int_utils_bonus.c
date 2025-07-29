/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 14:18:14 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_sign(int n, t_flags *flags)
{
	int	count;

	count = 0;
	if (n < 0)
		count += write(1, "-", 1);
	else if (flags->plus)
		count += write(1, "+", 1);
	else if (flags->space)
		count += write(1, " ", 1);
	return (count);
}

int	print_precision_padding(int count)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	while (i < count)
	{
		printed += write(1, "0", 1);
		i++;
	}
	return (printed);
}

int	handle_right_padding(int len, t_flags *flags)
{
	int	count;
	int	padding;
	int	i;

	count = 0;
	padding = flags->width - len;
	if (padding > 0)
	{
		if (flags->zero && flags->dot < 0 && !flags->minus)
			count += print_precision_padding(padding);
		else
		{
			i = 0;
			while (i < padding)
			{
				count += write(1, " ", 1);
				i++;
			}
		}
	}
	return (count);
}

int	handle_left_padding(int len, t_flags *flags)
{
	int	count;
	int	padding;
	int	i;

	count = 0;
	i = 0;
	padding = flags->width - len;
	while (i < padding)
	{
		count += write(1, " ", 1);
		i++;
	}
	return (count);
}

int	print_number_with_flags(t_num_data *data, t_flags *flags)
{
	int	count;
	int	total_len;

	count = 0;
	total_len = calculate_total_length(
			data->n, data->num_len, data->precision_padding, flags);
	if (!flags->minus)
		count += handle_right_padding(total_len, flags);
	count += print_sign(data->n, flags);
	count += print_precision_padding(data->precision_padding);
	count += write(1, data->num_str, data->num_len);
	if (flags->minus)
		count += handle_left_padding(total_len, flags);
	return (count);
}
