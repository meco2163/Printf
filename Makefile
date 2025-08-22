# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 05:41:00 by mekaplan          #+#    #+#              #
#    Updated: 2025/08/22 02:13:50 by mekaplan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar
ARFLAGS     = rcs

LIBFT_DIR   = Libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_OBJS  = $(LIBFT_DIR)/*.o

INCLUDES        = -I.
BONUS_INCLUDES  = -I. -I$(LIBFT_DIR)

SRCS        = ft_printf.c \
              ft_printf_utils.c \
              ft_print_char.c \
              ft_print_string.c \
              ft_print_int.c \
              ft_print_unsigned.c \
              ft_print_hex.c \
              ft_print_percent.c 

BONUS_SRCS  = ft_printf_bonus.c \
              ft_print_char_bonus.c \
              ft_print_string_bonus.c \
              ft_print_int_bonus.c \
              ft_print_int_utils_bonus.c \
              ft_print_unsigned_bonus.c \
              ft_print_hex_bonus.c \
              ft_print_hex_utils_bonus.c \
              ft_print_pointer_bonus.c \
              ft_print_percent_bonus.c \
              ft_flags_bonus.c \
              ft_flags_utils_bonus.c

OBJS        = $(SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	rm -f $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS) $(LIBFT_OBJS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
