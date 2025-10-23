# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 13:44:26 by nguinot-          #+#    #+#              #
#    Updated: 2025/10/23 17:51:10 by nguinot-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
NAME_BONUS = fdf_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Imlx

SRC_DIR = src
INCLUDES_DIR = includes
MLX = -Lmlx -lmlx -lm -lXext -lX11

SRC = draw.c ft_split.c gnl_utils.c gnl.c libft.c nettoyage.c parser_utils.c \
      parser.c projection.c setup.c utils_colors.c utils.c zothers.c zothers2.c \
      zothers3.c zothers4.c

SRC_MAIN = main.c
BONUS_SRC = controls_bonus.c projection_bonus.c draw_projec_bonus.c zothers_bonus.c
BONUS_SRC_MAIN = main_bonus.c

OBJ = $(addprefix $(SRC_DIR)/,$(SRC:.c=.o))
OBJ_MAIN = $(addprefix $(SRC_DIR)/,$(SRC_MAIN:.c=.o))
BONUS_OBJ = $(addprefix $(SRC_DIR)/,$(BONUS_SRC:.c=.o))
BONUS_OBJ_MAIN = $(addprefix $(SRC_DIR)/,$(BONUS_SRC_MAIN:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -o $(NAME)

bonus: $(OBJ) $(BONUS_OBJ) $(BONUS_OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(BONUS_OBJ) $(BONUS_OBJ_MAIN) $(MLX) -o $(NAME_BONUS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_MAIN) $(BONUS_OBJ) $(BONUS_OBJ_MAIN)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re

