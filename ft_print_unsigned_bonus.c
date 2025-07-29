/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:36:49 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 10:36:58 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;

	tmp = n;
	len = 1;
	while (tmp /= 10)
		len++;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = '0' + (n % 10);
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
		return (0);
	count = handle_print(num_str, flags);
	free(num_str);
	return (count);
}

static int handle_print_unsigned(char *str, t_flags *flags)
{
    int count;
    int len;
    int padding;
    int precision_pad;
    int min_val;
    char pad_char;

    count = 0;
    len = ft_strlen(str);

    if (flags->dot >= 0 && flags->dot < len)
        len = flags->dot;

    if (!flags->minus)
    {
        if (flags->dot > ft_strlen(str))
            min_val = flags->dot;
        else
            min_val = len;

        padding = flags->width - min_val;
        if (padding > 0)
        {
            if (flags->zero && flags->dot == -1)
                pad_char = '0';
            else
                pad_char = ' ';
            count += put_padding(padding, pad_char);
        }
    }

    if (flags->dot > len)
    {
        precision_pad = flags->dot - len;
        count += put_padding(precision_pad, '0');
    }

    write(1, str, len);
    count += len;

    if (flags->minus)
    {
        if (flags->dot > ft_strlen(str))
            min_val = flags->dot;
        else
            min_val = len;

        padding = flags->width - min_val;
        if (padding > 0)
            count += put_padding(padding, ' ');
    }
    return (count);
}
