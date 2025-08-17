/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:40:22 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 05:52:21 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static int	print_unsigned_leftpad(t_flags *flags, int padding)
{
	int	count;

	count = 0;
	if (!flags->minus)
	{
		if (flags->zero && flags->dot == -1)
			count += put_padding(padding, '0');
		else
			count += put_padding(padding, ' ');
	}
	return (count);
}

static int	print_unsigned_rightpad(t_flags *flags, int padding)
{
	int	count;

	count = 0;
	if (flags->minus)
		count += put_padding(padding, ' ');
	return (count);
}

static int	handle_print_unsigned(char *num_str, t_flags *flags)
{
	int	count;
	int	len;
	int	precision_pad;
	int	padding;

	len = ft_strlen(num_str);
	if (flags->dot > len)
		precision_pad = flags->dot - len;
	else
		precision_pad = 0;
	padding = flags->width - (len + precision_pad);
	if (padding < 0)
		padding = 0;
	count = 0;
	count += print_unsigned_leftpad(flags, padding);
	count += put_padding(precision_pad, '0');
	count += ft_putnstr_fd(num_str, len, 1);
	count += print_unsigned_rightpad(flags, padding);
	return (count);
}

static char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;
	int				i;

	tmp = n;
	len = 1;
	tmp /= 10;
	while (tmp != 0)
	{
		len++;
		tmp /= 10;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = len;
	while (i > 0)
	{
		i--;
		str[i] = (char)('0' + (n % 10));
		n /= 10;
	}
	return (str);
}

int	ft_print_unsigned_bonus(t_flags *flags, va_list args)
{
	unsigned int	n;
	char			*num_str;
	int				count;

	n = va_arg(args, unsigned int);
	if (n == 0 && flags->dot == 0)
		num_str = ft_strdup("");
	else
		num_str = ft_utoa(n);
	if (!num_str)
		return (0);
	count = handle_print_unsigned(num_str, flags);
	free(num_str);
	return (count);
}
