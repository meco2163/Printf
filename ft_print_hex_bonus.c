/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:37:00 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 05:51:52 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static int	print_prefix(t_flags *flags, unsigned long n, char f)
{
	if (f == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (2);
	}
	if (flags->hash && n != 0)
	{
		if (f == 'x')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
		return (2);
	}
	return (0);
}

static int	null_pointer_case(t_flags *flags, char format)
{
	int	pad;
	int	count;

	if (format == 'p')
	{
		pad = flags->width - 5;
		if (pad < 0)
			pad = 0;
		count = 0;
		if (!flags->minus)
			count += put_padding(pad, ' ');
		ft_putstr_fd("(nil)", 1);
		count += 5;
		if (flags->minus)
			count += put_padding(pad, ' ');
		return (count);
	}
	pad = flags->width;
	count = 0;
	if (!flags->minus)
		count += put_padding(pad, ' ');
	if (flags->minus)
		count += put_padding(pad, ' ');
	return (count);
}

static t_hex_params	compute_hex_params(const char *s, t_flags *flags,
			unsigned long n, char format)
{
	t_hex_params	p;
	int				total;

	p.len = ft_strlen(s);
	p.dotpad = 0;
	if (flags->dot > p.len)
		p.dotpad = flags->dot - p.len;
	p.prefix_len = calc_prefix_len(flags, n, format);
	total = p.prefix_len + p.dotpad + p.len;
	p.pad = flags->width - total;
	if (p.pad < 0)
		p.pad = 0;
	return (p);
}

static int	print_hex_core(unsigned long n,
			const char *s, t_flags *flags, char format)
{
	t_hex_params	p;
	int				count;

	p = compute_hex_params(s, flags, n, format);
	count = 0;
	if (flags->zero && flags->dot < 0 && !flags->minus)
	{
		count += print_prefix(flags, n, format);
		count += put_padding(p.pad, '0');
	}
	else
	{
		if (!flags->minus)
			count += put_padding(p.pad, ' ');
		count += print_prefix(flags, n, format);
	}
	count += put_padding(p.dotpad, '0');
	ft_putstr_fd((char *)s, 1);
	count += p.len;
	if (flags->minus)
		count += put_padding(p.pad, ' ');
	return (count);
}

int	ft_print_hex_bonus(t_flags *flags, va_list args, char format)
{
	unsigned long	n;
	char			*s;
	int				count;

	if (format == 'p')
	{
		n = (unsigned long)va_arg(args, void *);
		if (n == 0)
			return (null_pointer_case(flags, format));
	}
	else
		n = (unsigned int)va_arg(args, unsigned int);
	s = ft_ultoa_base(n, format == 'X');
	if (!s)
		return (0);
	if (is_zero_case(flags, n))
	{
		free(s);
		return (null_pointer_case(flags, format));
	}
	count = print_hex_core(n, s, flags, format);
	free(s);
	return (count);
}
