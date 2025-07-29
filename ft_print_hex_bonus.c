/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:36:15 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 14:25:09 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <stdlib.h>

static char	*ft_ultoa_base(unsigned long n, int is_upper)
{
	char			*base;
	char			*str;
	int				len;
	unsigned long	tmp;

	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = 1;
	tmp = n;
	tmp = n / 16;
	while (tmp != 0)
	{
		len++;
		tmp = tmp / 16;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[n % 16];
		n /= 16;
	}
	return (str);
}

static int	print_prefix(t_flags *flags, unsigned long n, char format)
{
	if (format == 'p')
		return (write(1, "0x", 2));
	if (flags->hash && n != 0)
	{
		if (format == 'x')
			return (write(1, "0x", 2));
		if (format == 'X')
			return (write(1, "0X", 2));
	}
	return (0);
}

static int	print_padding(t_flags *flags, int total_len, int is_zero)
{
	char	pad_char;

	if (!flags->minus && flags->width > total_len)
	{
		if (flags->zero && flags->dot < 0 && !is_zero)
			pad_char = '0';
		else
			pad_char = ' ';
		return (put_padding(flags->width - total_len, pad_char));
	}
	return (0);
}

static int	print_right_padding(t_flags *flags, int total_len)
{
	if (flags->minus && flags->width > total_len)
		return (put_padding(flags->width - total_len, ' '));
	return (0);
}

int	ft_print_hex_bonus(t_flags *flags, va_list args, char format)
{
	unsigned long	n;
	char			*hex_str;
	int				num_len;
	int				count;
	int				prefix_len;

	count = 0;
	if (format == 'p')
		n = (unsigned long)va_arg(args, void *);
	else
		n = (unsigned int)va_arg(args, unsigned int);
	if (n == 0 && flags->dot == 0)
		hex_str = ft_strdup("");
	else
		hex_str = ft_ultoa_base(n, format == 'X');
	if (!hex_str)
		return (0);
	num_len = ft_strlen(hex_str);
	prefix_len = 0;
	if ((flags->hash && n != 0
		&& (format == 'x' || format == 'X')) || format == 'p')
		prefix_len = 2;
	count += print_padding(flags, num_len + prefix_len, n == 0);
	count += print_prefix(flags, n, format);
	count += print_str(hex_str);
	count += print_right_padding(flags, num_len + prefix_len);
	free(hex_str);
	return (count);
}
