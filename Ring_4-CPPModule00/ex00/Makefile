# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atang <atang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 14:37:26 by atang             #+#    #+#              #
#    Updated: 2024/07/06 18:14:12 by atang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME		= megaphone
CC			= c++
RM			= rm -f
CPPFLAGS	= -Wall -Wextra -Werror -std=c++98
SRCS		= megaphone.cpp
OBJS		= $(SRCS:.cpp=.o)

# Colours

DEFAULT_COLOUR 	= \033[0m
RED 			= \033[1;31m
BLUE 			= \033[1;34m
GREEN 			= \033[1;32m
YELLOW 			= \033[1;33m

# Recipes

$(NAME):	$(OBJS)
			@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
			@echo "$(GREEN)Compiled executable: $(NAME)$(DEFAULT_COLOUR)"

all:		$(NAME)

$(OBJS): 	$(SRCS)
			@$(CC) $(CPPFLAGS) -c $< -o $@
			@echo "$(GREEN)Compiled object file(s): $(notdir $@)$(DEFAULT_COLOUR)"

clean:
			@$(RM) $(OBJS)
			@echo "$(RED)Deleted object file(s): $(OBJS)$(DEFAULT_COLOUR)"

fclean:	clean
			@$(RM) $(NAME)
			@echo "$(RED)Deleted executable: $(NAME)$(DEFAULT_COLOUR)"		

re:			fclean all

.PHONY:		all clean fclean re