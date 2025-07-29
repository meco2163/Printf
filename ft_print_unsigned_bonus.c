/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:36:49 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 13:58:39 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	get_effective_len(char *str, t_flags *flags)
{
	int	len;

	len = ft_strlen(str);
	if (flags->dot >= 0 && flags->dot < len)
		return (flags->dot);
	else
		return (len);
}

static int	print_unsigned_padding(t_flags *flags, int content_len, int is_left)
{
	int		padding;
	char	pad_char;

	padding = flags->width - content_len;
	if (padding <= 0)
		return (0);
	if (!is_left && flags->zero && flags->dot == -1)
		pad_char = '0';
	else
		pad_char = ' ';
	return (put_padding(padding, pad_char));
}

static int	handle_print_unsigned(char *str, t_flags *flags)
{
	int		count;
	int		len;
	int		precision_pad;
	int		total_len;

	count = 0;
	len = get_effective_len(str, flags);
	if (flags->dot > len)
		precision_pad = flags->dot - len;
	else
		precision_pad = 0;
	total_len = len + precision_pad;
	if (!flags->minus)
		count += print_unsigned_padding(flags, total_len, 0);
	count += print_precision_padding(precision_pad);
	count += write(1, str, len);
	if (flags->minus)
		count += print_unsigned_padding(flags, total_len, 1);
	return (count);
}

static char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;

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
	while (len--)
	{
		str[len] = '0' + (n % 10);
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
	count = handle_print(num_str, flags);
	free(num_str);
	return (count);
}
