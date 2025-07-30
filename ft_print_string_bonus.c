/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:35:53 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/30 22:04:44 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "Libft/libft.h"

static void	ft_putstrn(char *str, int n)
{
	int		i;

	i = 0;
	while (i < n && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

static int	get_print_len(const char *str, t_flags *flags)
{
	int		len;

	len = ft_strlen(str);
	if (flags->dot >= 0 && flags->dot < len)
		return (flags->dot);
	return (len);
}

int	ft_print_string_bonus(const char *str, t_flags *flags)
{
	int			print_len;
	int			padding;
	const char	*s;

	s = str;
	if (!s)
	{
		if (flags->dot < 0)
			s = "(null)";
		else
			s = "";
	}
	print_len = get_print_len(s, flags);
	padding = get_padding(flags->width, print_len);
	if (!flags->minus)
		put_padding(padding, ' ');
	ft_putstrn((char *)s, print_len);
	if (flags->minus)
		put_padding(padding, ' ');
	return (print_len + padding);
}
