# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 10:16:29 by qdeffaux          #+#    #+#              #
#    Updated: 2025/08/12 08:08:43 by qdeffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f

# Directories
LIBFT_DIR	= libft/
MLX_DIR		= minilibx/

# Source files
SRCS		= 	src/main.c \
			  src/init.c \
			  src/events.c \
			  src/mouse.c \
			  src/draw.c \
			  src/draw_utils.c \
			  src/transform.c \
			  src/color.c \
			  src/color_utils.c \
			  src/fdf_parser.c \
			  src/parser_utils.c \
			  src/cleanup.c

# Object files
OBJS		= $(SRCS:.c=.o)

# Libraries
LIBFT		= $(LIBFT_DIR)libft.a
MLX			= $(MLX_DIR)libmlx.a

# Includes
INCLUDES	= -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

# MLX flags (Linux)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# MLX flags (macOS) - Uncomment if on macOS
# MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

norm:
	norminette *.c *.h

.PHONY: all clean fclean re norm
