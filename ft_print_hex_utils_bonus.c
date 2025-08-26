/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:38 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/25 15:05:10 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"

int	add_count(int *count, int part)
{
	if (part < 0)
		return (-1);
	*count += part;
	return (0);
}

int	hexlen(unsigned long n)
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

int	write_padded_literal(
	t_flags *flags, t_hex_params *params, const char *s, int count)
{
	params->pad = get_padding(flags->width, params->len);
	if (!flags->minus)
	{
		params->part = put_padding(params->pad, ' ');
		if (params->part < 0)
			return (-1);
		count += params->part;
	}
	if (params->len > 0)
	{
		params->part = acc_write(1, s, params->len);
		if (params->part < 0)
			return (-1);
		count += params->part;
	}
	if (flags->minus)
	{
		params->part = put_padding(params->pad, ' ');
		if (params->part < 0)
			return (-1);
		count += params->part;
	}
	return (count);
}

int	emit_right_side(const char *s, t_flags *flags, t_hex_params *p)
{
	int	count;
	int	part;

	count = 0;
	part = put_padding(p->dotpad, '0');
	if (part < 0)
		return (-1);
	count += part;
	part = ft_putnstr_fd(s, p->len, 1);
	if (part < 0)
		return (-1);
	count += part;
	if (flags->minus)
	{
		part = put_padding(p->pad, ' ');
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}
