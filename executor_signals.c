/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:56:57 by cwon              #+#    #+#             */
/*   Updated: 2025/07/21 15:19:21 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "executor.h"

static void	ignore_parent_signals(t_sigaction *old_int, t_sigaction *old_quit)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_int);
	sigaction(SIGQUIT, &sa, old_quit);
}

static void	restore_parent_signals(t_sigaction *old_int, t_sigaction *old_quit)
{
	sigaction(SIGINT, old_int, 0);
	sigaction(SIGQUIT, old_quit, 0);
}

int	handle_parent_signals(pid_t pid)
{
	int			status;
	t_sigaction	old_int;
	t_sigaction	old_quit;

	ignore_parent_signals(&old_int, &old_quit);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		restore_parent_signals(&old_int, &old_quit);
		return (EXIT_FAILURE);
	}
	restore_parent_signals(&old_int, &old_quit);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}
