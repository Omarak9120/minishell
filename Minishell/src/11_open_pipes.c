/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_open_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:50:22 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 17:07:05 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*ls -l | grep minishell | wc -l
Command #1: cmd_exec = {"ls", "-l", NULL}
Command #2: cmd_exec = {"grep", "minishell", NULL}
Command #3: cmd_exec = {"wc", "-l", NULL}
later in the execve we do the dup2()*/

void	open_pipes(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	int		r_and_w_pipe[2];

	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node->next)
	{
		pipe(r_and_w_pipe);
		cmd_exec_node->write_pipe = r_and_w_pipe[1];
		cmd_exec_node->next->read_pipe = r_and_w_pipe[0];
		cmd_exec_node = cmd_exec_node->next;
	}
}
