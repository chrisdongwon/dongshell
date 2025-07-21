/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:35:33 by cwon              #+#    #+#             */
/*   Updated: 2025/07/21 15:17:35 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>

extern volatile sig_atomic_t	g_sig_flag;

void	reset_signal_handlers(void);
void	setup_signal_handlers(void);

#endif
