/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:37:11 by cwon              #+#    #+#             */
/*   Updated: 2025/07/21 15:17:41 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"
#include "signal_handler.h"

volatile sig_atomic_t	g_sig_flag = 0;

static void	sigint_handler(int signo)
{
	(void)signo;
	g_sig_flag = 1;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int signo)
{
	(void)signo;
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_handler = sigint_handler;
	sa_quit.sa_handler = sigquit_handler;
	if (sigemptyset(&sa_int.sa_mask) == -1)
		perror("sigemptyset (from setup_signal_handlers) failed");
	if (sigemptyset(&sa_quit.sa_mask) == -1)
		perror("sigemptyset (from setup_signal_handlers) failed");
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, 0) == -1)
		perror("sigaction (from setup_signal_handlers) failed");
	if (sigaction(SIGQUIT, &sa_quit, 0) == -1)
		perror("sigaction (from setup_signal_handlers) failed");
}
