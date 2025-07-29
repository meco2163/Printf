/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:38:02 by mekaplan          #+#    #+#             */
/*   Updated: 2025/07/29 10:38:06 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	int minus;
	int zero;
	int dot;
	int width;
	int precision;
	int hash;
	int space;
	int plus;
}	t_flags;

int		ft_printf_bonus(const char *format, ...);
int		parse_all_flags(const char **format, t_flags *flags, va_list args);

int		ft_print_char_bonus(int c, t_flags *flags);
int		ft_print_string_bonus(const char *str, t_flags *flags);
int		ft_print_int_bonus(int n, t_flags *flags);
int		ft_print_unsigned_bonus(t_flags *flags, va_list args);
int		ft_print_hex_bonus(t_flags *flags, va_list args, char format);
int		ft_print_percent_bonus(t_flags *flags);

int		put_padding(int width, char c);
int		get_padding(int width, int print_len);
int		print_padding(int count, char c);

int		print_sign(int n, t_flags *flags);
int		print_precision_padding(int count);
int		handle_right_padding(int len, t_flags *flags);
int		handle_left_padding(int len, t_flags *flags);
int		print_number_with_flags(int n, char *num_str, int num_len, int precision_padding, t_flags *flags);

#endif
