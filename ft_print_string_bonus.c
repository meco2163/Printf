/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:39:18 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 05:52:17 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static int	get_print_len(const char *s, t_flags *flags)
{
	int	len;

	len = ft_strlen(s);
	if (flags->dot >= 0 && flags->dot < len)
		return (flags->dot);
	return (len);
}

int	ft_print_string_bonus(const char *str, t_flags *flags)
{
	const char	*s;
	int			print_len;
	int			padding;
	int			count;

	if (!str)
	{
		if (flags->dot == -1 || flags->dot >= 6)
			s = "(null)";
		else
			s = "";
	}
	else
		s = str;
	print_len = get_print_len(s, flags);
	padding = get_padding(flags->width, print_len);
	count = 0;
	if (!flags->minus)
		count += put_padding(padding, ' ');
	count += ft_putnstr_fd(s, print_len, 1);
	if (flags->minus)
		count += put_padding(padding, ' ');
	return (count);
}
