# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 14:19:08 by mzhivoto          #+#    #+#              #
#    Updated: 2025/03/19 17:06:30 by mzhivoto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_CLIENT_BONUS = client_bonus.c
SRC_SERVER_BONUS = server_bonus.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
