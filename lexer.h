/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:09:16 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:45:10 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer.h
 * @brief Lexical analysis for the shell.
 *
 * This module defines token types, lexer structures, and functions
 * for converting an input command string into a list of tokens.
 * It handles operators, words, quoting, and token memory management.
 */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stddef.h>

/* Forward declarations */
typedef enum e_token_type	t_token_type;
typedef struct s_lexer		t_lexer;
typedef struct s_list		t_list;
typedef struct s_shell		t_shell;
typedef struct s_string		t_string;
typedef struct s_token		t_token;

struct						s_list;
struct						s_shell;
struct						s_string;

/**
 * @enum e_token_type
 * @brief Enumerates possible token types recognized by the lexer.
 */
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

/**
 * @struct s_lexer
 * @brief Stores lexer state and resulting token list.
 *
 * @var s_lexer::token_list
 *      Linked list of tokens produced by the lexer.
 * @var s_lexer::str
 *      Pointer to a dynamic string used during token assembly.
 */
struct s_lexer
{
	t_list		*token_list;
	t_string	*str;
};

/**
 * @struct s_token
 * @brief Represents a single token in the parsed input.
 *
 * @var s_token::value
 *      The string value of the token.
 * @var s_token::quote
 *      The quote character used, if any ('"', '\'', or 0).
 * @var s_token::type
 *      The type of token, from ::e_token_type.
 */
struct s_token
{
	char			*value;
	char			quote;
	t_token_type	type;
};

/* ====================== lexer_operator.c ====================== */
/**
 * @brief Parse an operator token from input.
 *
 * @param input Pointer to the current input position.
 * @param s     Pointer to the start of the operator string.
 *
 * @return Newly allocated token or NULL on failure.
 */
t_token			*handle_operator(const char **input, const char *s);

/* ====================== lexer_token_util.c ====================== */
/**
 * @brief Add an existing token to a token list.
 *
 * @param list  Pointer to the token list.
 * @param token Token to add.
 * @return true on success, false on allocation failure.
 */
bool			add_token(t_list **list, t_token *token);

/**
 * @brief Create and append a new token to a list.
 *
 * @param list  Pointer to the token list.
 * @param value Token string value.
 * @param type  Token type.
 * @param quote Quote character (0 if none).
 * @return true on success, false on allocation failure.
 */
bool			append_new_token(t_list **list, const char *value, \
t_token_type type, const char quote);

/**
 * @brief Allocate a new token object.
 *
 * @param start Pointer to the start of the token text.
 * @param len   Length of the token text.
 * @param type  Token type.
 * @param quote Quote character (0 if none).
 * @return Pointer to the new token or NULL on failure.
 */
t_token			*new_token(const char *start, size_t len, t_token_type type, \
char quote);

/**
 * @brief Determine the token type for an operator string.
 *
 * @param op Null-terminated operator string.
 * @return Matching token type or TOKEN_ERROR if unrecognized.
 */
t_token_type	get_token_type(const char *op);

/**
 * @brief Free a token object.
 *
 * @param arg Pointer to the token to free.
 */
void			free_token(void *arg);

/* ====================== lexer_token.c ====================== */
/**
 * @brief Get the next token from lexer input.
 *
 * @param lexer Pointer to lexer state.
 * @param input Pointer to the current input position.
 * @return Pointer to the next token or NULL at end of input.
 */
t_token			*get_next_token(t_lexer *lexer, const char **input);

/* ====================== lexer.c ====================== */
/**
 * @brief Perform lexical analysis on shell input.
 *
 * Converts the shell's current input line into a list of tokens
 * stored in the shell's lexer state.
 *
 * @param shell Pointer to the shell instance.
 * @return true on success, false on allocation failure.
 */
bool			lexer(t_shell *shell);

/**
 * @brief Free all memory used by the shell's lexer.
 *
 * Clears the token list and releases allocated buffers.
 *
 * @param shell Pointer to the shell instance.
 */
void			flush_lexer(t_shell *shell);

#endif /* LEXER_H */
