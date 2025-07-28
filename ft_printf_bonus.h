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
int		ft_print_char_bonus(char c, t_flags *flags);
int		ft_print_string_bonus(const char *str, t_flags *flags);
int		ft_print_int_bonus(int n, t_flags *flags);
int		ft_print_unsigned_bonus(unsigned int n, t_flags *flags);
int		ft_print_hex_bonus(unsigned int n, t_flags *flags, char spec);
int		ft_print_pointer_bonus(void *ptr, t_flags *flags);
int		ft_print_percent_bonus(t_flags *flags);
int		put_padding(int width, char c);

#endif
