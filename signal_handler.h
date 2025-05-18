/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:35:33 by cwon              #+#    #+#             */
/*   Updated: 2025/05/07 19:40:26 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# define _XOPEN_SOURCE 700

# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

# include "libft/libft.h"

extern volatile sig_atomic_t	g_sig_flag;

void	reset_signal_handlers(void);
void	setup_signal_handlers(void);

#endif
