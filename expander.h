/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:48:49 by cwon              #+#    #+#             */
/*   Updated: 2025/06/25 13:44:43 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"

typedef struct s_expander	t_expander;

struct s_expander
{
	bool		sub_error;
	const char	*ifs;
	int			last_exit_status;
	t_ast		*ast;
	t_list		*envp_list;
};

// expander_util.c
bool	ifs_delim(char c, const char *ifs);
bool	ifs_whitespace(char c, const char *ifs);

#endif
