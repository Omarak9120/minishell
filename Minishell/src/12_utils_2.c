/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:02:29 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/17 13:53:31 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

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
