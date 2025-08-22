/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:40:22 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/21 22:20:04 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "Libft/libft.h"
#include <stdlib.h>

static int	add_count(int *count, int part)
{
	if (part < 0)
		return (-1);
	*count += part;
	return (0);
}

static int	handle_print_unsigned(char *num_str, t_flags *flags)
{
	t_hex_params	f;
	int				count;

	f.len = (int)ft_strlen(num_str);
	f.dotpad = 0;
	if (flags->dot > f.len)
		f.dotpad = flags->dot - f.len;
	f.pad = get_padding(flags->width, f.len + f.dotpad);
	count = 0;
	if (add_count(&count, write_left_pad(flags, &f)) < 0)
		return (-1);
	if (add_count(&count, put_padding(f.dotpad, '0')) < 0)
		return (-1);
	if (add_count(&count, ft_putnstr_fd(num_str, f.len, 1)) < 0)
		return (-1);
	if (add_count(&count, write_right_pad(flags, &f)) < 0)
		return (-1);
	return (count);
}

static char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;
	int				i;

	tmp = n;
	len = 1;
	tmp /= 10;
	while (tmp != 0)
	{
		len++;
		tmp /= 10;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = len;
	while (i > 0)
	{
		i--;
		str[i] = (char)('0' + (n % 10));
		n /= 10;
	}
	return (str);
}

int	ft_print_unsigned_bonus(t_flags *flags, va_list args)
{
	unsigned int	n;
	char			*num_str;
	int				count;

	n = va_arg(args, unsigned int);
	if (n == 0 && flags->dot == 0)
		num_str = ft_strdup("");
	else
		num_str = ft_utoa(n);
	if (!num_str)
		return (-1);
	count = handle_print_unsigned(num_str, flags);
	free(num_str);
	return (count);
}
