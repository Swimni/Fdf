# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 13:44:26 by nguinot-          #+#    #+#              #
#    Updated: 2025/08/08 14:10:58 by nguinot-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
NAME_BONUS = fdf_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx

SRC = draw.c ft_split.c gnl_utils.c gnl.c libft.c nettoyage.c parser_utils.c \
parser.c projection.c setup.c utils_colors.c utils.c zothers.c zothers2.c \
zothers3.c zothers4.c

SRC_MAIN = main.c
BONUS_SRC = controls_bonus.c projection_bonus.c draw_projec_bonus.c \
zothers_bonus.c
BONUS_SRC_MAIN = main_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_MAIN = $(SRC_MAIN:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
BONUS_OBJ_MAIN = $(BONUS_SRC_MAIN:.c=.o)

MLX = -Lmlx -lmlx -lm -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -o $(NAME)

bonus: $(OBJ) $(BONUS_OBJ) $(BONUS_OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(BONUS_OBJ) $(BONUS_OBJ_MAIN) $(MLX) -o $(NAME_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_MAIN) $(BONUS_OBJ) $(BONUS_OBJ_MAIN)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re


