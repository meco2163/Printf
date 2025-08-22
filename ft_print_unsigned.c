/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:40:42 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:20:41 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_uint(unsigned int n, int *count)
{
	char	c;

	if (n >= 10)
	{
		if (put_uint(n / 10, count) < 0)
			return (-1);
	}
	c = (char)('0' + (n % 10));
	if (acc_write(count, &c, 1) < 0)
		return (-1);
	return (0);
}

int	ft_print_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (put_uint(n, &count) < 0)
		return (-1);
	return (count);
}
