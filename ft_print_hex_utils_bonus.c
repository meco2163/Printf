/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:44:23 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/30 13:43:11 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
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
