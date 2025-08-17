/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:38 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 05:51:56 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char	*select_base(int is_upper)
{
	if (is_upper)
		return ("0123456789ABCDEF");
	return ("0123456789abcdef");
}

static int	calculate_hex_len(unsigned long n)
{
	int	len;

	len = 1;
	n /= 16;
	while (n != 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static void	fill_hex_str(char *str, unsigned long n, char *base, int len)
{
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[n % 16];
		n /= 16;
	}
}

char	*ft_ultoa_base(unsigned long n, int is_upper)
{
	char	*base;
	char	*str;
	int		len;

	base = select_base(is_upper);
	len = calculate_hex_len(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	fill_hex_str(str, n, base, len);
	return (str);
}

int	is_zero_case(t_flags *flags, unsigned long n)
{
	return (n == 0 && flags->dot == 0);
}
