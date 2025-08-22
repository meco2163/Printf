/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:38:48 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 01:15:27 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	add_pad_count(int *count, int pad, char ch)
{
	int	part;

	part = put_padding(pad, ch);
	if (part < 0)
		return (-1);
	*count += part;
	return (0);
}

int	ft_print_percent_bonus(t_flags *flags)
{
	int		count;
	int		pad;
	char	padc;
	char	ch;

	count = 0;
	pad = get_padding(flags->width, 1);
	padc = ' ';
	if (!flags->minus && flags->zero)
		padc = '0';
	if (!flags->minus)
		if (add_pad_count(&count, pad, padc) < 0)
			return (-1);
	ch = '%';
	if (acc_write(&count, &ch, 1) < 0)
		return (-1);
	if (flags->minus)
		if (add_pad_count(&count, pad, ' ') < 0)
			return (-1);
	return (count);
}
