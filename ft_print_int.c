/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:38:18 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:03:43 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_uint(unsigned long n, int *count)
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

int	ft_print_int(int n)
{
	long	nn;
	int		count;

	count = 0;
	nn = (long)n;
	if (nn < 0)
	{
		if (acc_write(&count, "-", 1) < 0)
			return (-1);
		nn = -nn;
	}
	if (put_uint((unsigned long)nn, &count) < 0)
		return (-1);
	return (count);
}
