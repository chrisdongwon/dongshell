/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:11:54 by cwon              #+#    #+#             */
/*   Updated: 2025/07/10 17:19:02 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "envp.h"
#include "libft/libft.h"
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
		flush_and_exit(shell, "malloc", EXIT_FAILURE);
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

	hostname = get_envp_value(env_list, "HOSTNAME");
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

	username = get_envp_value(envp_list, "USER");
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
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	hostname = get_hostname(shell->envp_list);
	if (!hostname)
	{
		free(username);
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	}
	cwd = getcwd(0, 0);
	if (!cwd)
		cwd = ft_strdup("?");
	if (!cwd)
	{
		free(username);
		free(hostname);
		flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
	}
	return (build_prompt(shell, username, hostname, cwd));
}

void	read_command(t_shell *shell)
{
	shell->prompt = get_prompt(shell);
	shell->command = readline(shell->prompt);
	if (!shell->command)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		flush_and_exit(shell, 0, shell->last_exit_status);
	}
	if (*(shell->command))
		add_history(shell->command);
}
