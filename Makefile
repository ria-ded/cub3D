# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 20:36:45 by mdziadko          #+#    #+#              #
#    Updated: 2025/10/15 12:00:10 by svolkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# 								   VARIABLES								   #
# **************************************************************************** #

NAME		= cub3D
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g
AR			= ar rcs
RM			= rm -f

# Detect OS
UNAME := $(shell uname)

# Platform-specific MiniLibX path
ifeq ($(UNAME), Darwin)
	MLX_DIR		= minilibx-mms
	MLX_LIB		= $(MLX_DIR)/libmlx.dylib
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit \
				-Wl,-rpath,$(CURDIR)
else
	MLX_DIR		= minilibx-linux
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lX11 -lXext
endif

# Directories
LIBFT_DIR		= libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a
OBJ_DIR			= obj

# Includes and Libraries
INCLUDES		= -I. -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS			= $(LIBFT_LIB) $(MLX_LIB)

# **************************************************************************** #
# 									FILES									   #
# **************************************************************************** #

SRCS		= main.c parser/parser.c parser/parser_tex.c parser/parser_color.c \
			parser/parser_map_add.c parser/parser_map.c parser/parser_map_wall.c \
			src/cleanup.c src/print.c  src/init.c \
			render/render.c \
			rotation.c events.c project.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADERS		= includes/cub3D.h

# **************************************************************************** #
# 									RULES									   #
# **************************************************************************** #

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME) 

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLX_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR) || true

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(MLX_DIR) || true

re: fclean all

.PHONY: all clean fclean re