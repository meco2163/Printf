/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:35:33 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 05:51:42 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_print_char_bonus(char c, t_flags *flags)
{
	int	count;
	int	padding;

	count = 0;
	padding = 0;
	if (flags->width > 1)
		padding = flags->width - 1;
	if (flags->minus)
		flags->zero = 0;
	if (!flags->minus)
	{
		if (flags->zero)
			count += put_padding(padding, '0');
		else
			count += put_padding(padding, ' ');
	}
	count += write(1, &c, 1);
	if (flags->minus)
		count += put_padding(padding, ' ');
	return (count);
}
