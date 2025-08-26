/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 21:22:24 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 01:00:34 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	scan_meta_bonus(const char *p, const char **end_out)
{
	while (*p == '-' || *p == '0' || *p == '#' || *p == ' ' || *p == '+')
		p++;
	if (*p == '*')
		p++;
	else
		while (*p >= '0' && *p <= '9')
			p++;
	if (*p == '.')
	{
		p++;
		if (*p == '*')
			p++;
		else
			while (*p >= '0' && *p <= '9')
				p++;
	}
	*end_out = p;
	return (*p == 'c' || *p == 's' || *p == 'd' || *p == 'i'
		|| *p == 'u' || *p == 'x' || *p == 'X' || *p == 'p' || *p == '%');
}

int	precheck_format_bonus(const char *s)
{
	const char	*q;
	int			ok;

	while (*s)
	{
		if (*s != '%')
		{
			s++;
			continue ;
		}
		if (*(s + 1) == '\0')
			return (-1);
		ok = scan_meta_bonus(s + 1, &q);
		if (ok)
		{
			s = q + 1;
			continue ;
		}
		if (*q == '\0')
			return (-1);
		if ((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z'))
			return (-1);
		s = q;
	}
	return (0);
}

static int	emit_invalid_seq_core(
	const char **format, const char *p, const char *q)
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

int	emit_invalid_seq_bonus(const char **format, const char *start)
{
	const char	*p;
	const char	*q;

	p = start;
	q = p;
	while (*q && (*q == '-' || *q == '0' || *q == '#' || *q == ' '
			|| *q == '+' || *q == '*' || *q == '.'
			|| (*q >= '0' && *q <= '9')))
		q++;
	return (emit_invalid_seq_core(format, p, q));
}
