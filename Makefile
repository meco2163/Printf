# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 16:05:57 by mekaplan          #+#    #+#              #
#    Updated: 2025/07/27 13:26:03 by mekaplan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	=	libftprintf.a
CFLAGS  	=	-Wall -Wextra -Werror
CC      	=	cc

SRCS    	=	ft_printf.c				\
				ft_print_char.c			\
				ft_print_string.c		\
				ft_print_int.c			\
				ft_print_unsigned.c		\
				ft_print_hex.c			\
				ft_print_percent.c

BONUS_SRCS	=	ft_printf_bonus.c		\
				ft_flags_bonus.c		\
				ft_flags_bonus_utils.c

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: CFLAGS += -DBONUS
bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
