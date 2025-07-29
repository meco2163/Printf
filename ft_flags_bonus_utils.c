/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:34:58 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 10:35:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_put_padding(int width, char c)
{
	int	count;

	count = 0;
	while (width-- > 0)
		count += write(1, &c, 1);
	return (count);
}

int	get_padding(int width, int print_len)
{
	if (width > print_len)
		return (width - print_len);
	return (0);
}

int	print_padding(int count, char c)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
	return (count);
}
