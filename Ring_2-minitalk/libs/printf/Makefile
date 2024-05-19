# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sentry <sentry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 13:43:51 by atang             #+#    #+#              #
#    Updated: 2023/11/27 10:31:52 by sentry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   	= libftprintf.a

CC     	= gcc
CFLAGS 	= -Wall -Wextra -Werror
SRCS	= ft_character.c \
        	ft_hexadecimal.c \
           	ft_integer.c \
           	ft_pointer.c \
           	ft_printf.c \
           	ft_string.c \
           	ft_unsigned_decimal.c

TEST_SRCS	= test_main.c

OBJS	=	$(SRCS:.c=.o)

RM       = rm -f

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) -o test_program test_main.c -I./includes -L./ -lftprintf
	./test_program
	$(RM) test_program

.PHONY: all clean fclean re
