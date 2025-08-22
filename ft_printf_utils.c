/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:32:44 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 21:07:53 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	slen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_spec(int c)
{
	if (c == 'c')
		return (1);
	if (c == 's')
		return (1);
	if (c == 'd' || c == 'i')
		return (1);
	if (c == 'u')
		return (1);
	if (c == 'x' || c == 'X')
		return (1);
	if (c == 'p' || c == '%')
		return (1);
	return (0);
}

const char	*scan_meta_end(const char *p)
{
	while (*p && (*p == '-' || *p == '0' || *p == '#' || *p == ' '
			|| *p == '+' || *p == '*' || *p == '.'
			|| (*p >= '0' && *p <= '9')))
		p++;
	return (p);
}

int	acc_write(int *count, const void *s, int n)
{
	const char	*buf;
	int			i;
	int			w;

	buf = (const char *)s;
	i = 0;
	while (i < n)
	{
		w = write(1, buf + i, n - i);
		if (w <= 0)
			return (-1);
		i += w;
	}
	*count += n;
	return (0);
}

int	emit_literal(const char **format, int *count)
{
	const char	*p;
	int			len;

	p = *format;
	while (*p && *p != '%')
		p++;
	len = (int)(p - *format);
	if (len > 0)
	{
		if (acc_write(count, *format, len) < 0)
			return (-1);
	}
	*format = p;
	return (0);
}
