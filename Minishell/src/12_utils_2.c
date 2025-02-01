/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:09:31 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:09:34 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

/**
 *   Closes any input_fd, output_fd, read_pipe, or write_pipe for each command 
 *   node in the cmd_exec_list if they're not in the standard defaults 
 *   (0 for input, 1 for output, -1 for pipes).
 */

void	mini_close_all_fd(t_mini *mini)
{
	t_cmd	*cmd_exec_node;

	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		if (cmd_exec_node->input_fd != 0)
			close(cmd_exec_node->input_fd);
		if (cmd_exec_node->output_fd != 1)
			close(cmd_exec_node->output_fd);
		if (cmd_exec_node->read_pipe != -1)
			close(cmd_exec_node->read_pipe);
		if (cmd_exec_node->write_pipe != -1)
			close(cmd_exec_node->write_pipe);
		cmd_exec_node = cmd_exec_node->next;
	}
}
/**
 *   Closes all file descriptors (input_fd, output_fd, read_pipe, write_pipe)
 *   for a single command node, if they're open. Typically used when exiting 
 *   early due to redirection issues or cleaning up child processes.
 */

void	mini_close_node_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->input_fd != -1)
		close(cmd_exec_node->input_fd);
	if (cmd_exec_node->output_fd != -1)
		close(cmd_exec_node->output_fd);
	if (cmd_exec_node->read_pipe != -1)
		close(cmd_exec_node->read_pipe);
	if (cmd_exec_node->write_pipe != -1)
		close(cmd_exec_node->write_pipe);
}
/**
 Specifically closes the read_pipe and write_pipe in a single command node.
 */

void	mini_close_pipe_node_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->read_pipe != -1)
		close(cmd_exec_node->read_pipe);
	if (cmd_exec_node->write_pipe != -1)
		close(cmd_exec_node->write_pipe);
}

void	mini_close_pipes(t_mini *mini, t_cmd *current)
{
	t_cmd	*tmp;

	tmp = mini->cmd_exec_list;
	while (tmp)
	{
		if (tmp != current)
		{
			close(tmp->read_pipe);
			close(tmp->write_pipe);
		}
		tmp = tmp->next;
	}
}
