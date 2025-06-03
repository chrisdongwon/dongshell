/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:27:36 by cwon              #+#    #+#             */
/*   Updated: 2025/06/02 13:47:36 by cwon             ###   ########.fr       */
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

// envp_list.c
char	*get_env_value(t_list *envp_list, const char *key);
void	free_envp(void *arg);

#endif
