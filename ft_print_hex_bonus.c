/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:36:15 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/31 03:58:13 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"

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

int	null_pointer_case(t_flags *flags, char f)
{
	int	pad;
	int	cnt;

	if (f == 'p')
	{
		pad = flags->width - 5;
		if (pad < 0)
			pad = 0;
		cnt = 0;
		if (!flags->minus)
			cnt += put_padding(pad, ' ');
		ft_putstr_fd("(nil)", 1);
		cnt += 5;
		if (flags->minus)
			cnt += put_padding(pad, ' ');
		return (cnt);
	}
	pad = flags->width;
	cnt = 0;
	if (!flags->minus)
		cnt += put_padding(pad, ' ');
	if (flags->minus)
		cnt += put_padding(pad, ' ');
	return (cnt);
}

static t_hex_params	compute_hex_params(const char *s, t_flags *flags,
			unsigned long n, char f)
{
	t_hex_params	p;
	int				total;

	p.len = ft_strlen(s);
	p.dotpad = 0;
	if (flags->dot > p.len)
		p.dotpad = flags->dot - p.len;
	p.prefix_len = calc_prefix_len(flags, n, f);
	total = p.prefix_len + p.dotpad + p.len;
	p.pad = flags->width - total;
	if (p.pad < 0)
		p.pad = 0;
	return (p);
}

static int	print_hex_core(unsigned long n,
			const char *s, t_flags *flags, char f)
{
	t_hex_params	p;
	int				cnt;

	p = compute_hex_params(s, flags, n, f);
	cnt = 0;
	if (flags->zero && flags->dot < 0 && !flags->minus)
	{
		cnt += print_prefix(flags, n, f);
		cnt += put_padding(p.pad, '0');
	}
	else
	{
		if (!flags->minus)
			cnt += put_padding(p.pad, ' ');
		cnt += print_prefix(flags, n, f);
	}
	cnt += put_padding(p.dotpad, '0');
	cnt += write(1, s, p.len);
	if (flags->minus)
		cnt += put_padding(p.pad, ' ');
	return (cnt);
}

int	ft_print_hex_bonus(t_flags *flags, va_list args, char f)
{
	unsigned long	n;
	char			*s;
	int				cnt;

	if (f == 'p')
	{
		n = (unsigned long)va_arg(args, void *);
		if (n == 0)
			return (null_pointer_case(flags, f));
	}
	else
		n = (unsigned int)va_arg(args, unsigned int);
	s = ft_ultoa_base(n, f == 'X');
	if (!s)
		return (0);
	if (is_zero_case(flags, n))
	{
		free(s);
		return (null_pointer_case(flags, f));
	}
	cnt = print_hex_core(n, s, flags, f);
	free(s);
	return (cnt);
}
