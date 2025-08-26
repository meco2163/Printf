/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:35:48 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/25 14:30:21 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	int				count;
	unsigned char	ch;

	ch = (unsigned char)c;
	count = acc_write(1, &ch, 1);
	if (count < 0)
		return (-1);
	return (count);
}
