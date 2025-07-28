/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:01:46 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/27 12:52:40 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex_recursive(unsigned long n, char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_print_hex_recursive(n / 16, base);
	write(1, &base[n % 16], 1);
	count++;
	return (count);
}

int	ft_print_hex_lower(unsigned int n)
{
	return (ft_print_hex_recursive((unsigned long)n, "0123456789abcdef"));
}

int	ft_print_hex_upper(unsigned int n)
{
	return (ft_print_hex_recursive((unsigned long)n, "0123456789ABCDEF"));
}

int	ft_print_pointer(unsigned long ptr)
{
	int	count;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_print_hex_recursive(ptr, "0123456789abcdef");
	return (count);
}
