/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:27:36 by cwon              #+#    #+#             */
/*   Updated: 2025/07/30 13:08:29 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include <stdbool.h>

typedef struct s_envp	t_envp;
typedef struct s_list	t_list;
typedef struct s_shell	t_shell;

struct					s_list;
struct					s_shell;

struct s_envp
{
	bool	exported;
	char	*key;
	char	*value;
};

// envp_array.c
char	**list_to_envp_array(t_shell *shell, t_list *node);

// envp_set.c
void	set_env(t_shell *shell, const char *key, const char *value, \
bool exported);

// envp_util.c
char	*get_envp_value(t_list *envp_list, const char *key);
t_envp	*envp_to_node(t_shell *shell, const char *envp_str);
t_envp	*new_envp(t_shell *shell, const char *key, const char *value, \
bool exported);

// envp.c
t_envp	*get_envp(t_shell *shell, const char *key);
void	free_envp(void *arg);
void	init_envp(t_shell *shell, char **envp);

#endif
