/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:27:36 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 21:18:57 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "libft/libft.h"

typedef struct s_envp	t_envp;

struct s_envp
{
	bool	exported;
	char	*key;
	char	*value;
};

// envp_util.c
char		*combine_key_value(t_envp *envp);
t_list		*new_envp_node(const char *env_str);

// envp.c
char		**list_to_envp_array(t_list *envp_list);
const char	*get_env_value(t_list *envp_list, const char *key);
t_list		*envp_to_list(char **envp);
void		free_envp_array(char **envp);
void		free_envp(void *arg);

#endif
