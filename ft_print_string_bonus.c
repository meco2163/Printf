/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:39:18 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/25 14:56:57 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"

static int	get_print_len(const char *s, t_flags *f)
{
	int	len;

	len = ft_strlen(s);
	if (f->dot >= 0 && f->dot < len)
		return (f->dot);
	return (len);
}

static const char	*select_source(const char *str, t_flags *f)
{
	if (!str)
	{
		if (f->dot >= 0 && f->dot < 6)
			return ("");
		return ("(null)");
	}
	return (str);
}

static int	write_pad_if(int cond, int padding)
{
	int	part;

	if (!cond)
		return (0);
	part = put_padding(padding, ' ');
	if (part < 0)
		return (-1);
	return (part);
}

static int	write_string_flow(const char *s, int len, t_flags *f)
{
	int	count;
	int	padding;
	int	part;

	count = 0;
	padding = get_padding(f->width, len);
	part = write_pad_if(!f->minus, padding);
	if (part < 0)
		return (-1);
	count += part;
	part = ft_putnstr_fd(s, len, 1);
	if (part < 0)
		return (-1);
	count += part;
	part = write_pad_if(f->minus, padding);
	if (part < 0)
		return (-1);
	count += part;
	return (count);
}

int	ft_print_string_bonus(const char *str, t_flags *flags)
{
	const char	*s;
	int			len;

	s = select_source(str, flags);
	len = get_print_len(s, flags);
	return (write_string_flow(s, len, flags));
}
