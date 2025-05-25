/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:32:40 by cwon              #+#    #+#             */
/*   Updated: 2025/05/25 23:17:44 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(char *username, char *hostname, char *cwd)
{
	char	*result;
	size_t	len;

	len = ft_strlen(username) + ft_strlen(hostname) + ft_strlen(cwd) + 5;
	result = malloc(len);
	if (!result)
	{
		perror("malloc (from build_prompt) failed");
		free(username);
		free(hostname);
		free(cwd);
		return (0);
	}
	result[0] = 0;
	ft_strlcat(result, username, len);
	ft_strlcat(result, "@", len);
	ft_strlcat(result, hostname, len);
	ft_strlcat(result, ":", len);
	ft_strlcat(result, cwd, len);
	ft_strlcat(result, "$ ", len);
	free(username);
	free(hostname);
	free(cwd);
	return (result);
}

static char	*get_hostname(t_list *env_list)
{
	char		*newline;
	char		buffer[_SC_HOST_NAME_MAX];
	const char	*hostname;
	int			fd;
	ssize_t		bytes_read;

	hostname = get_env_value(env_list, "HOSTNAME");
	if (hostname && *hostname)
		return (ft_strdup(hostname));
	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("localhost"));
	bytes_read = read(fd, buffer, _SC_HOST_NAME_MAX - 1);
	close(fd);
	if (bytes_read <= 0)
		return (ft_strdup("localhost"));
	buffer[bytes_read] = 0;
	newline = ft_strchr(buffer, '\n');
	if (newline)
		*newline = 0;
	return (ft_strdup(buffer));
}

static char	*get_username(t_list *envp_list)
{
	const char	*username;

	username = get_env_value(envp_list, "USER");
	if (username && *username)
		return (ft_strdup(username));
	return (ft_strdup("unknown_user"));
}

char	*get_prompt(t_list *envp_list)
{
	char	*cwd;
	char	*hostname;
	char	*username;

	username = get_username(envp_list);
	hostname = get_hostname(envp_list);
	cwd = getcwd(0, 0);
	if (!cwd)
		cwd = ft_strdup("?");
	return (build_prompt(username, hostname, cwd));
}
