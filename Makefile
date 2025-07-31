# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 16:05:57 by mekaplan          #+#    #+#              #
#    Updated: 2025/07/31 03:30:00 by mekaplan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs

LIBFT_DIR   = Libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_OBJS  = $(LIBFT_DIR)/*.o

SRCS        = ft_printf.c \
              ft_print_char.c \
              ft_print_string.c \
              ft_print_int.c \
              ft_print_unsigned.c \
              ft_print_hex.c \
              ft_print_percent.c

BONUS_SRCS  = ft_printf.c \
              ft_print_char_bonus.c \
              ft_print_string_bonus.c \
              ft_print_int_bonus.c \
              ft_print_int_utils_bonus.c \
              ft_print_unsigned_bonus.c \
              ft_print_hex_bonus.c \
              ft_print_hex_utils_bonus.c \
              ft_print_percent_bonus.c \
              ft_flags_bonus.c \
              ft_flags_bonus_utils.c

OBJS        = $(SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

INCLUDES    = -I. -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(AR) $(NAME) $(OBJS) $(LIBFT_OBJS)

bonus: $(BONUS_OBJS)
	@make -C $(LIBFT_DIR)
	$(AR) $(NAME) $(BONUS_OBJS) $(LIBFT_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
