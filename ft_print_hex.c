/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:25 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 22:32:33 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_hex(unsigned long n, const char *base)
{
	char	buffer[20];
	int		i;
	int		count;
	int		part;

	i = 0;
	if (n == 0)
		buffer[i++] = base[0];
	while (n > 0)
	{
		buffer[i++] = base[n % 16];
		n /= 16;
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

static int	ft_print_hex_lower(unsigned int n)
{
	return (put_hex((unsigned long)n, "0123456789abcdef"));
}

static int	ft_print_hex_upper(unsigned int n)
{
	return (put_hex((unsigned long)n, "0123456789ABCDEF"));
}

static int	ft_print_pointer(unsigned long ptr)
{
	int	count;
	int	part;

	if (ptr == 0)
	{
		count = acc_write(1, "(nil)", 5);
		if (count < 0)
			return (-1);
		return (count);
	}
	count = acc_write(1, "0x", 2);
	if (count < 0)
		return (-1);
	part = put_hex(ptr, "0123456789abcdef");
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

int	ft_print_hex(char c, va_list args)
{
	int	count;

	if (c == 'x')
		return (ft_print_hex_lower(va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_print_hex_upper(va_arg(args, unsigned int)));
	if (c == 'p')
		return (ft_print_pointer(va_arg(args, unsigned long)));
	count = acc_write(1, &c, 1);
	if (count < 0)
		return (-1);
	return (count);
}
