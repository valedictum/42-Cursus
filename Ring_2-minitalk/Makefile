# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sentry <sentry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 19:22:44 by atang             #+#    #+#              #
#    Updated: 2023/12/07 03:03:27 by sentry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER      = server
CLIENT      = client
SERVER_BONUS = server_bonus
CLIENT_BONUS  = client_bonus

CC          = gcc
RM          = rm -f
AR          = ar
CFLAGS      = -Wall -Wextra -Werror -I$(PRINTF_DIR)/includes -I$(INCS)

ROOT_DIR    = $(shell pwd)
PRINTF_DIR  = $(ROOT_DIR)/libs/printf
INCS        = $(ROOT_DIR)/incs

LIBRARY     = -L$(PRINTF_DIR) -lftprintf

SRC_DIR     = $(ROOT_DIR)/srcs/minitalk
SERVER_SRC  = $(SRC_DIR)/server.c
CLIENT_SRC  = $(SRC_DIR)/client.c
SERVER_BONUS_SRC  = $(SRC_DIR)/server_bonus.c
CLIENT_BONUS_SRC  = $(SRC_DIR)/client_bonus.c

LIBFTPRINTF = $(PRINTF_DIR)/libftprintf.a
LIBFTPRINTF_SRC = $(shell find $(PRINTF_DIR) -name '*.c')
LIBFTPRINTF_OBJ = $(LIBFTPRINTF_SRC:.c=.o)

all: $(LIBFTPRINTF) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

$(LIBFTPRINTF): $(LIBFTPRINTF_OBJ)
	$(AR) rcs $@ $^

$(SERVER): $(SERVER_SRC) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $^ -o $(SERVER) $(LIBRARY)

$(SERVER_BONUS): $(SERVER_BONUS_SRC) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $^ -o $(SERVER_BONUS) $(LIBRARY)

$(CLIENT): $(CLIENT_SRC) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $^ -o $(CLIENT) $(LIBRARY)

$(CLIENT_BONUS): $(CLIENT_BONUS_SRC) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $^ -o $(CLIENT_BONUS) $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(LIBFTPRINTF_OBJ)

fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS) $(LIBFTPRINTF)

re: fclean all

.PHONY: all clean fclean re
