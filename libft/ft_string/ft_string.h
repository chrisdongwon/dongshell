/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:53:48 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:14:08 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdbool.h>

typedef struct s_string	t_string;

struct s_string
{
	char	*buffer;
	size_t	capacity;
	size_t	size;
};

bool	append_char(t_string *str, char c);
bool	append_string(t_string *str, const char *ptr);
bool	init_string(t_string *str);
void	free_string(t_string *str);

#endif
