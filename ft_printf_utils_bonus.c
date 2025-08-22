/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 21:22:24 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 02:45:32 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_zero_case(t_flags *flags, unsigned long n)
{
	if (n == 0 && flags->dot == 0)
		return (1);
	return (0);
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

int	acc_write(int fd, const void *s, int count)
{
	const char	*buf;
	int			i;
	int			w;

	buf = (const char *)s;
	i = 0;
	while (i < count)
	{
		w = write(fd, buf + i, count - i);
		if (w < 0)
			return (-1);
		i += w;
	}
	return (count);
}

static int	emit_invalid_seq_core(const char **format,
				const char *p, const char *q)
{
	int	count;
	int	ret;

	count = 0;
	ret = acc_write(1, "%", 1);
	if (ret < 0)
		return (-1);
	count += ret;
	ret = acc_write(1, p, (int)(q - p));
	if (ret < 0)
		return (-1);
	count += ret;
	if (*q && !((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z')))
	{
		ret = acc_write(1, q, 1);
		if (ret < 0)
			return (-1);
		count += ret;
		q++;
	}
	*format = q;
	return (count);
}

int	emit_invalid_seq_bonus(const char **format, const char *start)
{
	const char	*p;
	const char	*q;

	p = start;
	q = scan_meta_end(p);
	if (*q == '\0')
	{
		*format = q;
		return (-1);
	}
	return (emit_invalid_seq_core(format, p, q));
}
