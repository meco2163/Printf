/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:39:30 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 02:26:06 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	slen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_print_string(char *s)
{
	int	count;
	int	len;
	int	part;

	if (!s)
		return (acc_write(1, "(null)", 6));
	len = slen(s);
	count = 0;
	if (len > 0)
	{
		part = acc_write(1, s, len);
		if (part < 0)
			return (-1);
		count += part;
	}
	return (count);
}
