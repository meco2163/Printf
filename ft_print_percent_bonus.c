/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:36:35 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/30 22:15:07 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "Libft/libft.h"
#include <unistd.h>

int	ft_print_percent_bonus(t_flags *flags)
{
	int		count;
	int		pad;
	char	padc;

	if (flags->width > 1)
		pad = flags->width - 1;
	else
		pad = 0;
	if (flags->zero && !flags->minus)
		padc = '0';
	else
		padc = ' ';
	count = 0;
	if (!flags->minus)
		count += put_padding(pad, padc);
	ft_putchar_fd('%', 1);
	count += 1;
	if (flags->minus)
		count += put_padding(pad, ' ');
	return (count);
}
