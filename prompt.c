/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:11:54 by cwon              #+#    #+#             */
/*   Updated: 2025/06/02 15:16:08 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(t_shell *shell, char *user, char *host, char *cwd)
{
	char	*result;
	size_t	len;

	len = ft_strlen(user) + ft_strlen(host) + ft_strlen(cwd) + 5;
	result = malloc(len);
	if (!result)
	{
		free(user);
		free(host);
		free(cwd);
		error_exit(shell, "malloc");
	}
	result[0] = 0;
	ft_strlcat(result, user, len);
	ft_strlcat(result, "@", len);
	ft_strlcat(result, host, len);
	ft_strlcat(result, ":", len);
	ft_strlcat(result, cwd, len);
	ft_strlcat(result, "$ ", len);
	free(user);
	free(host);
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

static char	*get_prompt(t_shell *shell)
{
	char	*cwd;
	char	*hostname;
	char	*username;

	username = get_username(shell->envp_list);
	if (!username)
		error_exit(shell, "ft_strdup");
	hostname = get_hostname(shell->envp_list);
	if (!hostname)
	{
		free(username);
		error_exit(shell, "ft_strdup");
	}
	cwd = getcwd(0, 0);
	if (!cwd)
		cwd = ft_strdup("?");
	if (!cwd)
	{
		free(username);
		free(hostname);
		error_exit(shell, "ft_strdup");
	}
	return (build_prompt(shell, username, hostname, cwd));
}

void	read_command(t_shell *shell)
{
	shell->prompt = get_prompt(shell);
	shell->command = readline(shell->prompt);
	if (!shell->command)
	{
		printf("exit\n");
		flush_shell(shell);
		ft_lstclear(&shell->envp_list, free_envp);
		exit(EXIT_SUCCESS);
	}
	if (*(shell->command))
		add_history(shell->command);
}
