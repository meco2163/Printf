/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:35:29 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 19:19:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_print_char_bonus(char c, t_flags *flags)
{
	int	count;
	int	padding;

	count = 0;
	padding = 0;
	if (flags->width > 1)
		padding = flags->width - 1;
	if (flags->minus == 0)
	{
		if (flags->zero)
			count += put_padding(padding, '0');
		else
			count += put_padding(padding, ' ');
	}
	count += write(1, &c, 1);
	if (flags->minus == 1)
		count += put_padding(padding, ' ');
	return (count);
}
