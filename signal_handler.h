/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:35:33 by cwon              #+#    #+#             */
/*   Updated: 2025/08/03 10:40:45 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_handler.h
 * @brief Signal handling interface for the shell.
 *
 * This module provides functions to set up and reset signal handlers
 * for interactive shell use. It also exposes a global signal flag that
 * can be checked by the main loop to react to signals.
 */
#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>

/**
 * @brief Global signal flag set by handlers.
 *
 * This volatile flag is set by signal handlers to indicate that a
 * signal has occurred. It should be checked by the shell's main loop.
 */
extern volatile sig_atomic_t	g_sig_flag;

/**
 * @brief Reset all signal handlers to their default actions.
 *
 * Restores the default handling for signals that the shell overrides.
 */
void	reset_signal_handlers(void);

/**
 * @brief Install custom signal handlers for the shell.
 *
 * Sets up handlers for signals such as SIGINT and SIGQUIT to allow
 * the shell to respond gracefully to user interrupts.
 */
void	setup_signal_handlers(void);

#endif /* SIGNAL_HANDLER_H */
