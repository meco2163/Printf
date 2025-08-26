/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:40:22 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 22:33:50 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static t_hex_params	compute_unsigned_params(const char *num_str, t_flags *flags)
{
	t_hex_params	params;
	int				total;

	params.len = (int)ft_strlen(num_str);
	params.dotpad = 0;
	if (flags->dot > params.len)
		params.dotpad = flags->dot - params.len;
	total = params.len + params.dotpad;
	params.pad = get_padding(flags->width, total);
	params.prefix_len = 0;
	params.part = 0;
	return (params);
}

static int	emit_unsigned_flow(const char *num_str, t_flags *flags,
			t_hex_params *params)
{
	int	count;
	int	part;

	count = 0;
	part = write_left_pad(flags, params);
	if (part < 0)
		return (-1);
	count += part;
	part = put_padding(params->dotpad, '0');
	if (part < 0)
		return (-1);
	count += part;
	part = ft_putnstr_fd(num_str, params->len, 1);
	if (part < 0)
		return (-1);
	count += part;
	part = write_right_pad(flags, params);
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

static int	handle_print_unsigned(char *num_str, t_flags *flags)
{
	t_hex_params	params;

	params = compute_unsigned_params(num_str, flags);
	return (emit_unsigned_flow(num_str, flags, &params));
}

static char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;
	int				i;

	tmp = n;
	len = 1;
	tmp /= 10;
	while (tmp != 0)
	{
		len++;
		tmp /= 10;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = len;
	while (i > 0)
	{
		i--;
		str[i] = (char)('0' + (n % 10));
		n /= 10;
	}
	return (str);
}

int	ft_print_unsigned_bonus(t_flags *flags, va_list args)
{
	unsigned int	n;
	char			*num_str;
	int				count;

	n = va_arg(args, unsigned int);
	if (n == 0 && flags->dot == 0)
	{
		num_str = ft_strdup("");
		if (!num_str)
			return (-1);
	}
	else
	{
		num_str = ft_utoa(n);
		if (!num_str)
			return (-1);
	}
	count = handle_print_unsigned(num_str, flags);
	free(num_str);
	return (count);
}
