/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:35:48 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:04:12 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	int		count;
	char	ch;

	count = 0;
	ch = (char)c;
	if (acc_write(&count, &ch, 1) < 0)
		return (-1);
	return (count);
}
