# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sentry <sentry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 16:35:36 by atang             #+#    #+#              #
#    Updated: 2024/05/17 10:33:13 by sentry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CC				= gcc
RM				= -rm -f
CFLAGS			= -Wall -Wextra -Werror -I$(INCS) -g -fsanitize=address

# Define colours 
DEFAULT_COLOUR = \033[0m
RED = \033[1;31m
BLUE = \033[1;34m
GREEN = \033[1;32m
YELLOW = \033[1;33m

ROOT_DIR		= $(shell pwd)
SRC_DIR			= $(ROOT_DIR)/srcs

.SILENT:

SRCS	=	getters_setters.c dinner.c init.c synchro_utils.c monitor.c utils.c write.c safe.c parse.c main.c
OBJS	= 	$(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))
INCS	= 	$(ROOT_DIR)/INCS

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -I$(INCS) $(OBJS) -o $(NAME)
		@echo "$(GREEN)Compiled executable: $(NAME)$(DEFAULT_COLOUR)"

all: $(NAME)

$(OBJS): $(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/philo.h
		$(CC) $(CFLAGS) -c $< -o $@
		@echo "$(GREEN)Compiled object file: $(notdir $@)$(DEFAULT_COLOUR)"

clean:
		$(RM) $(OBJS)
		@echo "$(RED)Deleted object files: $(notdir $(OBJS))$(DEFAULT_COLOUR)"

fclean: clean
		$(RM) $(NAME)
		@echo "$(RED)Deleted executable: $(NAME)$(DEFAULT_COLOUR)"

re: fclean all

.PHONY: all clean fclean re