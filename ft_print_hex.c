/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:25 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:02:06 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_hex(unsigned long n, const char *base, int *count)
{
	if (n >= 16)
	{
		if (put_hex(n / 16, base, count) < 0)
			return (-1);
	}
	if (acc_write(count, &base[n % 16], 1) < 0)
		return (-1);
	return (0);
}

int	ft_print_hex_lower(unsigned int n)
{
	int	count;

	count = 0;
	if (put_hex((unsigned long)n, "0123456789abcdef", &count) < 0)
		return (-1);
	return (count);
}

int	ft_print_hex_upper(unsigned int n)
{
	int	count;

	count = 0;
	if (put_hex((unsigned long)n, "0123456789ABCDEF", &count) < 0)
		return (-1);
	return (count);
}

int	ft_print_pointer(unsigned long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
	{
		if (acc_write(&count, "(nil)", 5) < 0)
			return (-1);
		return (count);
	}
	if (acc_write(&count, "0x", 2) < 0)
		return (-1);
	if (put_hex(ptr, "0123456789abcdef", &count) < 0)
		return (-1);
	return (count);
}

int	ft_print_hex(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'x')
		return (ft_print_hex_lower(va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_print_hex_upper(va_arg(args, unsigned int)));
	if (c == 'p')
		return (ft_print_pointer(va_arg(args, unsigned long)));
	if (acc_write(&count, &c, 1) < 0)
		return (-1);
	return (count);
}
