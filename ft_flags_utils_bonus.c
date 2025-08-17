/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:34:58 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 03:34:50 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"

int	put_padding(int width, char c)
{
	int	count;

	count = 0;
	while (width-- > 0)
	{
		ft_putchar_fd(c, 1);
		count++;
	}
	return (count);
}

int	get_padding(int width, int print_len)
{
	if (width > print_len)
		return (width - print_len);
	return (0);
}

int	ft_putnstr_fd(const char *s, int n, int fd)
{
	int	count;

	if (!s || n <= 0)
		return (0);
	count = 0;
	while (s[count] && count < n)
	{
		ft_putchar_fd(s[count], fd);
		count++;
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
