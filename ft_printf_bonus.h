/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:38:02 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/30 23:27:48 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		dot;
	int		width;
	int		precision;
	int		hash;
	int		space;
	int		plus;
}	t_flags;

typedef struct s_num_data
{
	int		n;
	char	*num_str;
	int		num_len;
	int		precision_padding;
}	t_num_data;

typedef struct s_hex_params
{
	int	len;
	int	dotpad;
	int	prefix_len;
	int	pad;
}	t_hex_params;

int		ft_print_char_bonus(char c, t_flags *flags);
int		ft_print_string_bonus(const char *str, t_flags *flags);
int		ft_print_int_bonus(int n, t_flags *flags);
int		ft_print_unsigned_bonus(t_flags *flags, va_list args);
int		ft_print_hex_bonus(t_flags *flags, va_list args, char format);
int		ft_print_percent_bonus(t_flags *flags);

int		ft_printf_bonus(const char *format, ...);
int		parse_all_flags(const char **format, t_flags *flags, va_list args);
int		put_padding(int width, char c);
int		get_padding(int width, int print_len);
int		print_padding(int count, char c);
int		print_precision_padding(int count);
int		print_number_with_flags(t_num_data *data, t_flags *flags);
int		calc_prefix_len(t_flags *flags, unsigned long n, char format);
char	*get_hex_str(
			t_flags *flags, va_list args, char format, unsigned long *n);

char	*ft_ultoa_base(unsigned long n, int is_upper);
#endif
