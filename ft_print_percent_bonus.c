/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:36:35 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 10:36:39 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int ft_print_percent_bonus(t_flags *flags)
{
    int     count;
    int     padding;
    char    pad_char;

    count = 0;
    if (flags->width > 1)
        padding = flags->width - 1;
    else
        padding = 0;
    if (flags->zero && !flags->minus)
        pad_char = '0';
    else
        pad_char = ' ';
    if (!flags->minus)
        count += put_padding(padding, pad_char);
    count += write(1, "%", 1);
    if (flags->minus)
        count += put_padding(padding, ' ');
    return count;
}
