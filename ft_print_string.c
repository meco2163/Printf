/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:39:30 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 20:34:44 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(char *s)
{
	int	count;
	int	len;

	count = 0;
	if (!s)
	{
		if (acc_write(&count, "(null)", 6) < 0)
			return (-1);
		return (count);
	}
	len = slen(s);
	if (len > 0)
	{
		if (acc_write(&count, s, len) < 0)
			return (-1);
	}
	return (count);
}
