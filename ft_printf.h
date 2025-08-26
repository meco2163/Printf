/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 05:36:47 by mekaplan          #+#    #+#             */
/*   Updated: 2025/08/27 02:26:27 by mekaplan         ###   ########.fr       */
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
	int		len;
	int		dotpad;
	int		prefix_len;
	int		pad;
	int		part;
}	t_hex_params;

int				ft_printf(const char *format, ...);

int				ft_print_char(int c);
int				ft_print_string(char *s);
int				ft_print_int(int n);
int				ft_print_unsigned(unsigned int n);
int				ft_print_hex(char c, va_list args);
int				ft_print_percent(void);

int				ft_print_char_bonus(char c, t_flags *flags);
int				ft_print_string_bonus(const char *str, t_flags *flags);
int				ft_print_int_bonus(int n, t_flags *flags);
int				ft_print_unsigned_bonus(t_flags *flags, va_list args);
int				ft_print_hex_bonus(t_flags *flags, va_list args, char format);
int				ft_print_pointer_bonus(t_flags *flags, va_list args);
int				ft_print_percent_bonus(t_flags *flags);

int				acc_write(int fd, const void *s, int count);
int				emit_invalid_seq(const char **format);
int				scan_meta(const char *p, const char **end_out);

int				emit_invalid_seq_bonus(const char **format, const char *start);
int				precheck_format_bonus(const char *s);
int				parse_all_flags(
					const char **format, t_flags *flags, va_list args);
int				put_padding(int width, char c);
int				get_padding(int width, int print_len);
int				ft_putnstr_fd(const char *s, int count, int fd);
int				calc_prefix_len(t_flags *flags, unsigned long n, char format);
int				pre_left_stage(t_num_data *d, t_flags *f, t_hex_params *params);
int				body_and_tail(t_flags *f, t_hex_params *params, t_num_data *d);
int				add_count(int *count, int part);
int				hexlen(unsigned long n);
int				guard_trailing_percent(const char **format);
int				emit_right_side(const char *s, t_flags *flags, t_hex_params *p);
int				write_left_pad(t_flags *flags, t_hex_params *params);
int				write_right_pad(t_flags *flags, t_hex_params *params);
int				write_hex_left_pad(
					t_flags *flags, t_hex_params *params, int zero_mode);
int				write_padded_literal(t_flags *flags, t_hex_params *params,
					const char *s, int count);

char			*ft_ultoa_base(unsigned long n, int is_upper);
t_hex_params	compute_hex_params(const char *s, t_flags *flags,
					unsigned long n, char format);

#endif