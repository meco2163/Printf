/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:32:44 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 03:02:42 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	scan_meta(const char *p, const char **end_out)
{
	while (*p && (*p == '-' || *p == '0' || *p == '#' || *p == ' '
			|| *p == '+' || *p == '*' || *p == '.'
			|| (*p >= '0' && *p <= '9')))
		p++;
	*end_out = p;
	if (*p == 'c' || *p == 's' || *p == 'd' || *p == 'i'
		|| *p == 'u' || *p == 'x' || *p == 'X' || *p == 'p'
		|| *p == '%')
		return (1);
	return (0);
}

static int	emit_invalid_seq_core(const char **format,
		const char *p, const char *q)
{
	(void)p;
	if (*q == '\0')
		return (-1);
	if ((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z'))
	{
		if (acc_write(1, "%", 1) < 0)
			return (-1);
		*format = q + 1;
		return (1);
	}
	if (acc_write(1, "%", 1) < 0)
		return (-1);
	*format = q;
	return (1);
}

int	emit_invalid_seq(const char **format)
{
	const char	*p;
	const char	*q;

	p = *format + 1;
	if (*p == '\0')
	{
		*format = p;
		return (-1);
	}
	if (!scan_meta(p, &q))
	{
		if (*q == '\0')
		{
			*format = q;
			return (-1);
		}
		return (emit_invalid_seq_core(format, p, q));
	}
	return (-1);
}

int	acc_write(int fd, const void *s, int count)
{
	const char	*buf;
	int			i;
	int			w;

	buf = (const char *)s;
	i = 0;
	while (i < count)
	{
		w = write(fd, buf + i, count - i);
		if (w < 0)
			return (-1);
		i += w;
	}
	return (count);
}
