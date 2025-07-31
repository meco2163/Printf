/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:35:43 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/31 01:48:17 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
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

int	print_precision_padding(int count)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	while (i < count)
	{
		printed += write(1, "0", 1);
		i++;
	}
	return (printed);
}

int	ft_print_int_bonus(int n, t_flags *flags)
{
	char		*num_str;
	int			num_len;
	int			precision_padding;
	int			count;
	t_num_data	data;

	precision_padding = 0;
	num_str = create_num_str(n, flags);
	if (!num_str)
		return (-1);
	num_len = ft_strlen(num_str);
	if (flags->dot >= 0 && flags->dot > num_len)
		precision_padding = flags->dot - num_len;
	data.n = n;
	data.num_str = num_str;
	data.num_len = num_len;
	data.precision_padding = precision_padding;
	count = print_number_with_flags(&data, flags);
	free(num_str);
	return (count);
}
