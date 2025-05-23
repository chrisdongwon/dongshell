/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:30:50 by cwon              #+#    #+#             */
/*   Updated: 2025/05/23 10:06:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(const char *user, const char *host, char *cwd)
{
	char		*result;
	t_string	str;

	if (!init_string(&str))
	{
		free(cwd);
		return (0);
	}
	append_string(&str, user);
	append_string(&str, "@");
	append_string(&str, host);
	append_string(&str, ":");
	append_string(&str, cwd);
	append_string(&str, "$ ");
	free(cwd);
	result = ft_strdup(str.buffer);
	free_string(&str);
	return (result);
}

static void	get_hostname(char *host)
{
	char	*newline;
	int		fd;
	ssize_t	bytes_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
	{
		ft_strlcpy(host, "unknown_host", 13);
		return ;
	}
	bytes_read = read(fd, host, _SC_HOST_NAME_MAX - 1);
	close(fd);
	if (bytes_read <= 0)
	{
		ft_strlcpy(host, "unknown_host", 13);
		return ;
	}
	host[bytes_read] = 0;
	newline = ft_strchr(host, '\n');
	if (newline)
		*newline = 0;
}

char	*generate_prompt(void)
{
	char		*cwd;
	char		host[_SC_HOST_NAME_MAX];
	const char	*user;

	user = getenv("USER");
	if (!user)
		user = "unknown_user";
	get_hostname(host);
	cwd = getcwd(0, 0);
	if (!cwd)
		cwd = ft_strdup("unknown_dir");
	return (build_prompt(user, host, cwd));
}
