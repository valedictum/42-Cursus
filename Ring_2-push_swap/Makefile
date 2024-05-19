# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sentry <sentry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 14:44:36 by atang             #+#    #+#              #
#    Updated: 2024/02/25 12:05:50 by sentry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= push_swap
CC				= gcc
RM 				= rm -f
CFLAGS 			= -g -Wall -Wextra -Werror -I$(PRINTF_DIR) -I$(INCS) -g
LIBRARY 		= -L$(PRINTF_DIR) -lftprintf

.SILENT:

ROOT_DIR 		= $(shell pwd)
PRINTF_DIR 		= $(ROOT_DIR)/libs/printf
SRC_DIR 		= $(ROOT_DIR)/srcs/push_swap

SRCS	= 	push_swap.c \
			check.c \
			chunk.c \
			chunk_utils.c \
			error.c \
			memory.c \
			operations_push.c \
			operations_reverse_rotate.c \
			operations_rotate.c \
        	operations_swap.c \
           	parse.c \
			sort_helpers.c \
			sort_small.c \
			sort_large.c \
			split.c \
			stack.c \

OBJS			= $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

INCS = $(ROOT_DIR)/incs

$(NAME): $(OBJS)
	make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) -I $(INCS) -I $(PRINTF_DIR) $(OBJS) -o $(NAME) $(LIBRARY)

all: $(NAME)

$(OBJS): $(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INCS) -I $(PRINTF_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re