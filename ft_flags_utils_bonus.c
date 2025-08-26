/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:35:10 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/26 22:30:31 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

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
		if (w < 0)
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
		if (w < 0)
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

int	acc_write(int fd, const void *s, int count)
{
	const char	*buf;
	int			i;
	int			w;
	int			attempts;

	buf = (const char *)s;
	i = 0;
	attempts = 0;
	while (i < count)
	{
		w = write(fd, buf + i, count - i);
		if (w < 0)
			return (-1);
		if (w == 0)
		{
			attempts++;
			if (attempts > 1000)
				return (-1);
		}
		else
			attempts = 0;
		i += w;
	}
	return (count);
}
