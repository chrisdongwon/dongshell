# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 23:18:05 by cwon              #+#    #+#              #
#    Updated: 2025/05/23 09:23:49 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER = \
	ast.h \
	lexer.h \
	minishell.h \
	parser.h \
	signal_handler.h
SRC = \
	ast.c \
	flush.c \
	init.c \
	lexer_util.c \
	lexer.c \
	minishell_util.c \
	minishell.c \
	parser_command.c \
	parser_redir.c \
	parser_subshell.c \
	parser_util.c \
	parser.c \
	prompt.c \
	signal_handler.c \
	token.c
MAIN = main.c
OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

BONUS_HEADER = \
	minishell_bonus.h
BONUS_SRC = \
	minishell_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o) $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LDFLAGS)

bonus: $(BONUS_EXEC)

$(BONUS_EXEC): $(LIBFT) $(OBJ) $(BONUS_OBJ) $(HEADER) $(BONUS_HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(BONUS_OBJ) -o $(BONUS_EXEC) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(BONUS_EXEC)

re: fclean all

.PHONY: all clean fclean re bonus
