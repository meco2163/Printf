/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:34:58 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/31 01:48:52 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"

int	put_padding(int width, char c)
{
	int	count;

	count = 0;
	while (width-- > 0)
		count += write(1, &c, 1);
	return (count);
}

int	get_padding(int width, int print_len)
{
	if (width > print_len)
		return (width - print_len);
	return (0);
}

int	print_padding(int count, char c)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
	return (count);
}

int	calc_prefix_len(t_flags *flags, unsigned long n, char format)
{
	if ((flags->hash && n != 0
			&& (format == 'x' || format == 'X')) || format == 'p')
		return (2);
	return (0);
}

char	*get_hex_str(
	t_flags *flags, va_list args, char format, unsigned long *n)
{
	if (format == 'p')
		*n = (unsigned long)va_arg(args, void *);
	else
		*n = (unsigned int)va_arg(args, unsigned int);
	if (*n == 0 && flags->dot == 0)
		return (ft_strdup(""));
	return (ft_ultoa_base(*n, format == 'X'));
}
