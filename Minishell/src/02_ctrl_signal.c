/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_ctrl_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:27:21 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:38:29 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
//This means “when the program receives SIGINT (Ctrl+C),
 call the function sig_handler
//No special flags
//Installs int_action for SIGINT
*/

void	mini_ctrl_signal(t_mini *mini)
{
	struct sigaction	int_action;
	struct sigaction	quit_action;

	int_action.sa_handler = sig_handler;
	sigemptyset(&int_action.sa_mask);
	int_action.sa_flags = 0;
	sigaction(SIGINT, &int_action, NULL);
	quit_action.sa_handler = SIG_IGN;
	quit_action.sa_flags = 0;
	sigemptyset(&quit_action.sa_mask);
	sigaction(SIGQUIT, &quit_action, NULL);
	mini->int_action = int_action;
	mini->quit_action = quit_action;
}
