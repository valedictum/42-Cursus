# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atang <atang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/17 16:56:17 by atang             #+#    #+#              #
#    Updated: 2024/01/19 17:42:31 by atang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FDF = fdf

.SILENT:

CC = gcc
RM = rm -f
AR = ar
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)/includes -I$(FT_PRINTF_DIR)/includes -I$(INCS) -g

ROOT_DIR = $(shell pwd)
LIBFT_DIR = $(ROOT_DIR)/libs/libft
FT_PRINTF_DIR = $(ROOT_DIR)/libs/ft_printf
INCS = $(ROOT_DIR)/incs

LIBRARY = -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprint -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRC_DIR = $(ROOT_DIR)/srcs/
MLX_DIR = $(ROOT_DIR)/minilibx_macos/

LIBLIBFT = $(LIBFT_DIR)/libft.a
LIBLIBFT_SRC = $(shell find $(LIBFT_DIR) -name '*.c')
LIBLIBFT_OBJ = $(LIBLIBFT_SRC:.c=.o)

LIBFT_PRINTF = $(FT_PRINTF_DIR)/libftprint.a
LIBFT_PRINTF_SRC = $(shell find $(FT_PRINTF_DIR) -name '*.c')
LIBFT_PRINTF_OBJ = $(LIBFT_PRINTF_SRC:.c=.o)

SRC_FILES = error.c fdf.c draw_utils.c draw.c read_file.c get_next_line.c get_next_line_utils.c
OBJ_FILES = $(SRC_FILES:%.c=%.o)

all: build_minilibx $(LIBLIBFT) $(LIBFT_PRINTF) $(FDF)

$(LIBLIBFT): $(LIBLIBFT_OBJ)
	$(AR) rcs $@ $^

$(LIBFT_PRINTF): $(LIBFT_PRINTF_OBJ)
	$(AR) rcs $@ $^

$(FDF): $(OBJ_FILES) $(LIBLIBFT) $(LIBFT_PRINTF)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

build_minilibx:
	@echo "Building MiniLibX..."
	@cd $(MLX_DIR) && $(MAKE)

fclean_minilibx:
	@echo "Fully cleaning MiniLibX..."
	@$(MAKE) -C $(MLX_DIR) fclean

clean:
	$(RM) $(OBJ_FILES) $(LIBLIBFT_OBJ) $(LIBFT_PRINTF_OBJ)

fclean: clean fclean_minilibx
	$(RM) $(FDF) $(LIBLIBFT) $(LIBFT_PRINTF)

re: fclean all

.PHONY: all clean fclean re build_minilibx fclean_minilibx
