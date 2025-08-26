/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:40:42 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 22:32:05 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_uint(unsigned int n)
{
	char	buffer[12];
	int		i;
	int		count;
	int		part;

	i = 0;
	if (n == 0)
		buffer[i++] = '0';
	while (n > 0)
	{
		buffer[i++] = '0' + (n % 10);
		n /= 10;
	}
	count = 0;
	while (--i >= 0)
	{
		part = acc_write(1, &buffer[i], 1);
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

int	ft_print_unsigned(unsigned int n)
{
	return (put_uint(n));
}
