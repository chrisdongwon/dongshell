/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:56:57 by cwon              #+#    #+#             */
/*   Updated: 2025/07/19 22:36:34 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>

#include "executor.h"

void	ignore_parent_signals(t_sigaction *old_int, t_sigaction *old_quit)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_int);
	sigaction(SIGQUIT, &sa, old_quit);
}

void	restore_parent_signals(t_sigaction *old_int, t_sigaction *old_quit)
{
	sigaction(SIGINT, old_int, 0);
	sigaction(SIGQUIT, old_quit, 0);
}
