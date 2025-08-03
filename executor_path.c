/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:06:33 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:31:27 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "envp.h"
#include "executor.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Check if a given path is an executable file.
 *
 * Determines if the file at the specified path exists, is executable by
 * the user, and is not a directory.
 *
 * @param path Path to the file to check.
 * @return true if the path is an executable file, false otherwise.
 */
static bool	is_executable(const char *path)
{
	struct stat	st;

	return (!stat(path, &st) && (st.st_mode & S_IXUSR) && !S_ISDIR(st.st_mode));
}

/**
 * @brief Build a candidate executable path by concatenating directory and
 *        command.
 *
 * Allocates and returns a new string containing the directory, a slash,
 * and the command appended together. Returns NULL if allocation fails.
 *
 * @param dir     Directory path.
 * @param command Command name.
 * @return Pointer to the newly allocated candidate path string, or NULL on 
 *         failure.
 */
static char	*build_candidate(const char *dir, const char *command)
{
	char	*candidate;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(command) + 2;
	candidate = malloc(len);
	if (!candidate)
	{
		perror("malloc");
		return (0);
	}
	ft_strlcpy(candidate, dir, len);
	ft_strlcat(candidate, "/", len);
	ft_strlcat(candidate, command, len);
	return (candidate);
}

char	**get_path_dirs(t_list *envp_list)
{
	char	*path_env;

	path_env = get_envp_value(envp_list, "PATH");
	if (!path_env)
		path_env = "/bin:/usr/bin";
	return (ft_split(path_env, ':'));
}

char	*check_direct_path(t_shell *shell, const char *command)
{
	char	*result;

	result = 0;
	if (ft_strchr(command, '/'))
	{
		if (is_executable(command))
		{
			result = ft_strdup(command);
			if (!result)
				flush_and_exit(shell, "ft_strdup", EXIT_FAILURE);
		}
	}
	return (result);
}

char	*search_in_path(t_shell *shell, char **paths, const char *command)
{
	char	*candidate;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		candidate = build_candidate(paths[i], command);
		if (!candidate)
		{
			free_str_array(paths);
			flush_and_exit(shell, "build_candidate", EXIT_FAILURE);
		}
		if (is_executable(candidate))
			return (candidate);
		free(candidate);
		i++;
	}
	return (0);
}
