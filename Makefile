# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 23:18:05 by cwon              #+#    #+#              #
#    Updated: 2025/06/25 13:44:56 by cwon             ###   ########.fr        #
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
	envp.h \
	expander.h \
	lexer.h \
	minishell.h \
	parser.h \
	signal_handler.h
SRC = \
	ast.c \
	envp.c \
	expander_split.c \
	expander_util.c \
	expander_var.c \
	expander.c \
	lexer_operator.c \
	lexer_token_util.c \
	lexer_token.c \
	lexer.c \
	minishell_envp.c \
	minishell.c \
	parser_pipeline.c \
	parser_util.c \
	parser.c \
	prompt.c \
	signal_handler.c
MAIN = main.c
OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LDFLAGS)

bonus: all

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
