/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:35:10 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/22 02:39:47 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int	put_padding(int width, char c)
{
	int	i;
	int	w;

	if (width <= 0)
		return (0);
	i = 0;
	while (i < width)
	{
		w = write(1, &c, 1);
		if (w <= 0)
			return (-1);
		i += w;
	}
	return (width);
}

int	get_padding(int width, int print_len)
{
	if (width > print_len)
		return (width - print_len);
	return (0);
}

int	ft_putnstr_fd(const char *s, int count, int fd)
{
	int	i;
	int	w;

	if (!s || count <= 0)
		return (0);
	i = 0;
	while (s[i] && i < count)
	{
		w = write(fd, s + i, 1);
		if (w <= 0)
			return (-1);
		i += w;
	}
	return (i);
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