/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:31:11 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 11:44:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

/**
 * @brief Handle `cd -` by retrieving and printing the OLDPWD value.
 *
 * This function fetches the value of the `OLDPWD` environment variable
 * from the shell environment and prints it to `STDOUT`. If `OLDPWD`
 * is not set, an error message is printed to `STDERR`.
 *
 * @param shell Pointer to the shell state.
 * @return const char* The `OLDPWD` value, or NULL if not set.
 */
static const char	*handle_oldpwd(t_shell *shell)
{
	t_envp		*oldpwd;

	oldpwd = get_envp(shell, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd(oldpwd->value, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (oldpwd->value);
}

/**
 * @brief Determine the target directory for the `cd` command.
 *
 * This function checks the first argument after `cd`. If no argument
 * is given, it uses the `HOME` environment variable. If the argument
 * is `-`, it calls `handle_oldpwd()` to retrieve `OLDPWD`. Otherwise,
 * it returns the argument as the target path.
 *
 * @param shell     Pointer to the shell state.
 * @param argv_list List of command arguments.
 * @return const char* The target path for `cd`, or NULL on error.
 */
static const char	*cd_get_target(t_shell *shell, t_list *argv_list)
{
	const char	*argv_1;
	t_envp		*home;

	argv_1 = get_argv_value(argv_list, 1);
	if (!argv_1)
	{
		home = get_envp(shell, "HOME");
		if (!home || !home->value)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (0);
		}
		return (home->value);
	}
	if (!ft_strcmp(argv_1, "-"))
		return (handle_oldpwd(shell));
	return (argv_1);
}

/**
 * @brief Get the current working directory.
 *
 * This function calls `getcwd()` to retrieve the absolute path of the
 * current working directory. If the call fails, it prints an error
 * message.
 *
 * @return char* The current working directory path, or NULL on failure.
 *               The returned string must be freed by the caller.
 */
static char	*cd_get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		perror("cd");
	return (cwd);
}

static void	cd_update_envs(t_shell *shell, const char *oldpwd)
{
	char	*cwd;

	cwd = cd_get_cwd();
	if (!cwd)
		return ;
	set_env(shell, "OLDPWD", oldpwd, true);
	set_env(shell, "PWD", cwd, true);
	free(cwd);
}

int	builtin_cd(t_shell *shell, t_list *argv_list)
{
	char		*oldpwd;
	const char	*target;

	if (count_builtin_arguments(argv_list) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	target = cd_get_target(shell, argv_list);
	if (!target)
		return (1);
	oldpwd = cd_get_cwd();
	if (!oldpwd)
		return (1);
	if (chdir(target))
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	cd_update_envs(shell, oldpwd);
	free(oldpwd);
	return (0);
}
