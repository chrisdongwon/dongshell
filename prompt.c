/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:30:50 by cwon              #+#    #+#             */
/*   Updated: 2025/05/11 18:46:31 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(const char *user, const char *host, char *cwd)
{
	char	*result;
	size_t	len;

	len = ft_strlen(user) + ft_strlen(host) + ft_strlen(cwd) + 5;
	result = (char *)malloc(len);
	if (!result)
	{
		free(cwd);
		return (0);
	}
	result[0] = 0;
	ft_strlcat(result, user, len);
	ft_strlcat(result, "@", len);
	ft_strlcat(result, host, len);
	ft_strlcat(result, ":", len);
	ft_strlcat(result, cwd, len);
	ft_strlcat(result, "$ ", len);
	free(cwd);
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
		cwd = "unknown_dir";
	return (build_prompt(user, host, cwd));
}
