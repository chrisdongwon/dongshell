/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:48:49 by cwon              #+#    #+#             */
/*   Updated: 2025/07/28 14:26:09 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdbool.h>

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

struct s_expander
{
	bool		sub_error;
	const char	*ifs;
	int			last_exit_status;
	t_ast		*ast;
	t_list		*envp_list;
};

// expander_heredoc_util.c
bool	collect_heredoc(const char *delim, const char *filename);
// expander_heredoc.c
void	prepare_heredocs(t_shell *shell, t_ast *ast, int *i);

// expander_sort.c
t_list	*merge_token_nodes(t_list *a, t_list *b);
t_list	*merge_token(t_list *front, t_list *back);
t_list	*mergesort_token(t_list *list);

// expander_split.c
t_list	*replace_node(t_list **head, t_list *node, t_list *new_list);
void	expand_split(t_shell *shell, t_list **head, t_list **node);

// expander_util.c
bool	ifs_delim(char c, const char *ifs);
bool	ifs_whitespace(char c, const char *ifs);
char	*make_temp_filename(int i);

// expander_var.c
void	expand_variable(t_shell *shell, t_token *token);

// expander_wildcard.c
t_list	*expand_pattern(t_shell *shell, const char *pattern, \
t_token_type token_type);
void	expand_wildcard_list(t_shell *shell, t_list **list, bool is_argv);

// expander.c
bool	expander(t_shell *shell);
void	flush_expander(t_shell *shell);

#endif
