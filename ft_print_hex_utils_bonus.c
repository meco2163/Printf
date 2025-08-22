/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:38 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 03:37:21 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	hexlen(unsigned long n)
{
	int	len;

	len = 1;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

t_hex_params	compute_hex_params(const char *s, t_flags *flags,
			unsigned long n, char format)
{
	t_hex_params	params;
	int				total;

	params.len = (int)ft_strlen(s);
	params.dotpad = 0;
	if (flags->dot > params.len)
		params.dotpad = flags->dot - params.len;
	params.prefix_len = calc_prefix_len(flags, n, format);
	total = params.prefix_len + params.dotpad + params.len;
	params.pad = flags->width - total;
	if (params.pad < 0)
		params.pad = 0;
	params.part = 0;
	return (params);
}

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

int	write_padded_literal(t_flags *flags, t_hex_params *f, const char *s)
{
	int	count;

	f->pad = get_padding(flags->width, f->len);
	count = 0;
	if (!flags->minus)
	{
		f->part = put_padding(f->pad, ' ');
		if (f->part < 0)
			return (-1);
		count += f->part;
	}
	if (f->len > 0)
	{
		if (acc_write(&count, s, f->len) < 0)
			return (-1);
	}
	if (flags->minus)
	{
		f->part = put_padding(f->pad, ' ');
		if (f->part < 0)
			return (-1);
		count += f->part;
	}
	return (count);
}
