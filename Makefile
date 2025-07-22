# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 23:18:05 by cwon              #+#    #+#              #
#    Updated: 2025/07/22 15:51:13 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g # remove debug flag when finished
LDFLAGS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER = \
	ast.h \
	builtin.h \
	envp.h \
	executor.h \
	expander.h \
	lexer.h \
	minishell.h \
	parser.h \
	signal_handler.h
SRC = \
	ast.c \
	builtin_cd.c \
	builtin_echo.c \
	builtin_env.c \
	builtin_exit_util.c \
	builtin_exit.c \
	builtin_export_sort.c \
	builtin_export_util.c \
	builtin_export.c \
	builtin_pwd.c \
	builtin_unset.c \
	builtin_util.c \
	envp_array.c \
	envp_set.c \
	envp_util.c \
	envp.c \
	executor_builtin.c \
	executor_command.c \
	executor_path.c \
	executor_pipe.c \
	executor_process.c \
	executor_redir.c \
	executor_signals.c \
	executor_util.c \
	executor.c \
	expander_heredoc_util.c \
	expander_heredoc.c \
	expander_sort.c \
	expander_split.c \
	expander_util.c \
	expander_var.c \
	expander_wildcard.c \
	expander.c \
	lexer_operator.c \
	lexer_token_util.c \
	lexer_token.c \
	lexer.c \
	minishell_print.c \
	minishell.c \
	parser_pipeline.c \
	parser_redir.c \
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
