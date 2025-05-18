/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:09:16 by cwon              #+#    #+#             */
/*   Updated: 2025/05/13 20:00:26 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>

# include "libft/libft.h"

typedef enum e_token_type	t_token_type;
typedef struct s_lexer		t_lexer;
typedef struct s_token		t_token;

enum e_token_type
{
	TOKEN_AND,
	TOKEN_APPEND,
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_HEREDOC,
	TOKEN_OR,
	TOKEN_PAREN_CLOSE,
	TOKEN_PAREN_OPEN,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_WORD
};

struct s_lexer
{
	bool		success;
	t_string	str;
};

struct s_token
{
	char			*value;
	char			quote;
	t_token_type	type;
};

// lexer_util.c
bool			close_quotes(const char **s);
bool			open_quotes(const char **s, char *quote);
size_t			match_operator(const char *s, char *buffer);
t_token_type	get_token_type(const char *op);

// lexer.c
t_token			*get_next_token(t_lexer *lexer, const char **input);

// token.c
bool			add_token(t_list **lst, t_token *token);
t_token			*new_token(const char *start, size_t len, t_token_type type, \
char quote);
void			free_token(void *arg);

#endif
