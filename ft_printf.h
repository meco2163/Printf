/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:47 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/17 05:52:32 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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

int		ft_printf(const char *format, ...);

int		ft_print_char(int c);
int		ft_print_string(char *s);
int		ft_print_pointer(unsigned long ptr);
int		ft_print_int(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex_lower(unsigned int n);
int		ft_print_hex_upper(unsigned int n);
int		ft_print_percent(void);

int		ft_print_char_bonus(char c, t_flags *flags);
int		ft_print_string_bonus(const char *str, t_flags *flags);
int		ft_print_int_bonus(int n, t_flags *flags);
int		ft_print_unsigned_bonus(t_flags *flags, va_list args);
int		ft_print_hex_bonus(t_flags *flags, va_list args, char format);
int		ft_print_percent_bonus(t_flags *flags);

int		parse_all_flags(const char **format, t_flags *flags, va_list args);
int		put_padding(int width, char c);
int		get_padding(int width, int print_len);
int		ft_putnstr_fd(const char *s, int n, int fd);
int		print_precision_padding(int width);
int		print_number_with_flags(t_num_data *data, t_flags *flags);
int		calc_prefix_len(t_flags *flags, unsigned long n, char format);
int		is_zero_case(t_flags *flags, unsigned long n);

char	*ft_ultoa_base(unsigned long n, int is_upper);
char	*get_hex_str(
			t_flags *flags, va_list args, char format, unsigned long *n);

#endif
