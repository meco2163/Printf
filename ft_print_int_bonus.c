/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:35:43 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 10:35:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <stdlib.h>
#include <limits.h>

static char	*create_num_str(int n, t_flags *flags)
{
	if (n == INT_MIN)
		return (ft_strdup("2147483648"));
	if (n == 0 && flags->dot == 0)
		return (ft_strdup(""));
	if (n < 0)
		return (ft_itoa(-n));
	return (ft_itoa(n));
}

static int	calculate_total_length(int n, int num_len, int precision_padding, t_flags *flags)
{
	int	total_len;

	total_len = num_len + precision_padding;
	if (n < 0 || flags->plus || flags->space)
		total_len++;
	return (total_len);
}

int	ft_print_int_bonus(int n, t_flags *flags)
{
	char	*num_str;
	int		num_len;
	int		precision_padding;
	int		count;

	precision_padding = 0;
	num_str = create_num_str(n, flags);
	if (!num_str)
		return (-1);
	num_len = ft_strlen(num_str);
	if (flags->dot >= 0 && flags->dot > num_len)
		precision_padding = flags->dot - num_len;
	count = print_number_with_flags(n, num_str, num_len, precision_padding, flags);
	free(num_str);
	return (count);
}
