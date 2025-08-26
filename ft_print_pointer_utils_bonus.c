/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:05:17 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 00:54:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

char	*ft_ultoa_base(unsigned long n, int is_upper)
{
	const char	*digits;
	char		*str;
	int			len;

	if (is_upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = hexlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = digits[n % 16];
		n /= 16;
	}
	return (str);
}

int	write_hex_left_pad(t_flags *flags, t_hex_params *p, int zero_mode)
{
	if (flags->minus)
		return (0);
	if (zero_mode)
		return (put_padding(p->pad, '0'));
	return (put_padding(p->pad, ' '));
}

int	write_left_pad(t_flags *flags, t_hex_params *params)
{
	int	count;

	count = 0;
	if (!flags->minus)
	{
		if (flags->zero && flags->dot == -1)
			params->part = put_padding(params->pad, '0');
		else
			params->part = put_padding(params->pad, ' ');
		if (params->part < 0)
			return (-1);
		count += params->part;
	}
	return (count);
}

int	write_right_pad(t_flags *flags, t_hex_params *params)
{
	int	count;

	count = 0;
	if (flags->minus)
	{
		params->part = put_padding(params->pad, ' ');
		if (params->part < 0)
			return (-1);
		count += params->part;
	}
	return (count);
}
