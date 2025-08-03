/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:48:49 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 12:29:09 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expander.h
 * @brief Shell word expansion module.
 *
 * This module provides functions and data structures for performing
 * shell word expansions, including variable expansion, wildcard
 * expansion, heredoc processing, and field splitting according to
 * IFS.
 */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdbool.h>

/* Forward declarations */
typedef enum e_token_type	t_token_type;
typedef struct dirent		t_dirent;
typedef struct s_ast		t_ast;
typedef struct s_expander	t_expander;
typedef struct s_list		t_list;
typedef struct s_shell		t_shell;
typedef struct s_token		t_token;

enum						e_token_type;
struct						s_ast;
struct						s_list;
struct						s_shell;
struct						s_token;

/**
 * @struct s_expander
 * @brief Holds the state for the shell expander.
 *
 * Stores information needed during expansion, such as the IFS
 * value, last exit status, and references to the AST and
 * environment.
 */
struct s_expander
{
	bool		sub_error;
	const char	*ifs;
	int			last_exit_status;
	t_ast		*ast;
	t_list		*envp_list;
};

/* ================= expander_heredoc_util.c ================= */
/**
 * @brief Collects heredoc input lines until a delimiter is encountered.
 *
 * Repeatedly reads lines from stdin and writes them to the file descriptor
 * until the line matches the delimiter string or an error occurs.
 *
 * @param shell  Pointer to the shell state.
 * @param result Pointer to a boolean flag set to false on error or EOF.
 * @param fd     File descriptor to write the heredoc input to.
 * @param delim  The heredoc delimiter string indicating end of input.
 */
void	collect_heredoc_loop(t_shell *shell, bool *result, int fd, \
const char *delim);

/* ================= expander_heredoc.c ================= */
/**
 * @brief Prepare heredoc files for all heredocs in the AST.
 *
 * @param shell Pointer to the shell state.
 * @param ast   Pointer to the AST node.
 * @param i     Pointer to a heredoc counter.
 */
void	prepare_heredocs(t_shell *shell, t_ast *ast, int *i);

/* ================= expander_sort.c ================= */
/**
 * @brief Merge two sorted token lists into one.
 *
 * @param a Pointer to the first token list.
 * @param b Pointer to the second token list.
 * @return Merged sorted list.
 */
t_list	*merge_token_nodes(t_list *a, t_list *b);

/**
 * @brief Merge two sorted token lists by token order.
 *
 * @param front First list.
 * @param back  Second list.
 * @return Merged sorted list.
 */
t_list	*merge_token(t_list *front, t_list *back);

/**
 * @brief Sort a token list using merge sort.
 *
 * @param list Pointer to the list to sort.
 * @return Sorted list.
 */
t_list	*mergesort_token(t_list *list);

/* ================= expander_split.c ================= */
/**
 * @brief Replace a node in a list with a new list of nodes.
 *
 * @param head     Pointer to the list head pointer.
 * @param node     Node to replace.
 * @param new_list List of replacement nodes.
 * @return Pointer to the next node after replacement.
 */
t_list	*replace_node(t_list **head, t_list *node, t_list *new_list);

/**
 * @brief Perform field splitting on a node's token value.
 *
 * @param shell Pointer to the shell state.
 * @param head  Pointer to the list head pointer.
 * @param node  Pointer to the node pointer being processed.
 */
void	expand_split(t_shell *shell, t_list **head, t_list **node);

/* ================= expander_util.c ================= */
/**
 * @brief Check if a character is an IFS delimiter.
 *
 * @param c   Character to check.
 * @param ifs String containing IFS characters.
 * @return true if delimiter, false otherwise.
 */
bool	ifs_delim(char c, const char *ifs);

/**
 * @brief Check if a character is IFS whitespace.
 *
 * @param c   Character to check.
 * @param ifs String containing IFS characters.
 * @return true if whitespace, false otherwise.
 */
bool	ifs_whitespace(char c, const char *ifs);

/**
 * @brief Generate a temporary filename for a heredoc.
 *
 * @param i Index or identifier for the heredoc file.
 * @return Newly allocated filename string.
 */
char	*make_temp_filename(int i);

/**
 * @brief Open a heredoc temporary file.
 *
 * @param filename Path to the heredoc file.
 * @return File descriptor, or -1 on error.
 */
int		open_heredoc_file(const char *filename);

/**
 * @brief Prints a warning message that heredoc was terminated by EOF.
 * 
 * Prints to standard error a message indicating the here-document input 
 * was ended prematurely by an end-of-file (EOF) signal before the delimiter 
 * string was encountered.
 * 
 * @param delim The heredoc delimiter string that was expected.
 */
void	heredoc_eof_warning(const char *delim);

/* ================= expander_var.c ================= */
/**
 * @brief Expand a shell variable in a token.
 *
 * @param shell Pointer to the shell state.
 * @param token Pointer to the token to modify.
 */
void	expand_variable(t_shell *shell, t_token *token);

/* ================= expander_wildcard.c ================= */
/**
 * @brief Expand a wildcard pattern into matching filenames.
 *
 * @param shell       Pointer to the shell state.
 * @param pattern     Pattern to match.
 * @param token_type  Type of token for the matches.
 * @return List of matching token nodes.
 */
t_list	*expand_pattern(t_shell *shell, const char *pattern, \
t_token_type token_type);

/**
 * @brief Expand wildcards in a list of tokens.
 *
 * @param shell  Pointer to the shell state.
 * @param list   Pointer to the list pointer to modify.
 * @param is_argv Whether the list represents argv tokens.
 */
void	expand_wildcard_list(t_shell *shell, t_list **list, bool is_argv);

/* ================= expander.c ================= */
/**
 * @brief Perform expansion on all words in the AST.
 *
 * @param shell Pointer to the shell state.
 * @return true on success, false on error.
 */
bool	expander(t_shell *shell);

/**
 * @brief Release resources allocated by the expander.
 *
 * @param shell Pointer to the shell state.
 */
void	flush_expander(t_shell *shell);

#endif /* EXPANDER_H */
