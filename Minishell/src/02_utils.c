/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:50 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 16:39:16 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int signum)
{
	t_mini	*mini;

	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_redisplay();
		mini = get_address();
		mini->status = 130;
	}
}

void	sig_handler_heredoc(int signum)
{
	t_mini	*mini;

	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		mini = get_address();
		mini->status = 130;
	}
}
