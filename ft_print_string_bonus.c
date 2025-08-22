/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:39:18 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:41:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"

static int	get_print_len(const char *s, t_flags *flags)
{
	int	len;

	len = ft_strlen(s);
	if (flags->dot >= 0 && flags->dot < len)
		return (flags->dot);
	return (len);
}

static int	write_padded(const char *s, int len, t_flags *flags)
{
	int	count;
	int	padding;
	int	part;

	padding = get_padding(flags->width, len);
	count = 0;
	if (!flags->minus)
	{
		part = put_padding(padding, ' ');
		if (part < 0)
			return (-1);
		count += part;
	}
	part = ft_putnstr_fd(s, len, 1);
	if (part < 0)
		return (-1);
	count += part;
	if (flags->minus)
	{
		part = put_padding(padding, ' ');
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}

int	ft_print_string_bonus(const char *str, t_flags *flags)
{
	const char	*s;
	int			len;

	if (str)
		s = str;
	else
		s = "(null)";
	len = get_print_len(s, flags);
	return (write_padded(s, len, flags));
}
