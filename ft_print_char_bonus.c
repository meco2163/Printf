/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:35:33 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 02:38:02 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	emit_pad(t_hex_params *params, char ch)
{
	int	part;

	part = put_padding(params->pad, ch);
	if (part < 0)
		return (-1);
	params->part = part;
	return (part);
}

static char	choose_padc(t_flags *flags)
{
	if (!flags->minus && flags->zero)
		return ('0');
	return (' ');
}

static int	write_char_flow(char c, t_flags *flags, t_hex_params *params)
{
	int	count;
	int	part;

	count = 0;
	if (!flags->minus)
	{
		part = emit_pad(params, choose_padc(flags));
		if (part < 0)
			return (-1);
		count += part;
	}
	part = acc_write(1, &c, 1);
	if (part < 0)
		return (-1);
	count += part;
	if (flags->minus)
	{
		part = emit_pad(params, ' ');
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

int	ft_print_char_bonus(char c, t_flags *flags)
{
	t_hex_params	params;

	params.len = 1;
	params.dotpad = 0;
	params.prefix_len = 0;
	params.pad = get_padding(flags->width, 1);
	params.part = 0;
	return (write_char_flow(c, flags, &params));
}
