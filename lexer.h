/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:09:16 by cwon              #+#    #+#             */
/*   Updated: 2025/06/02 16:56:39 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	t_list		*token_list;
	t_string	*str;
};

struct s_token
{
	char			*value;
	char			quote;
	t_token_type	type;
};

// lexer_operator.c
t_token			*handle_operator(const char **input, const char *s);

// lexer_token_util.c
bool			add_token(t_list **list, t_token *token);
bool			append_new_token(t_list **list, const char *value, \
t_token_type type, const char quote);
t_token			*new_token(const char *start, size_t len, t_token_type type, \
char quote);
t_token_type	get_token_type(const char *op);
void			free_token(void *arg);

// lexer_token.c
t_token			*get_next_token(t_lexer *lexer, const char **input);

#endif
