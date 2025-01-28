/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:50:06 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/18 15:37:08 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

static int	mini_is_path_unseted(t_mini *mini);

void	mini_manage_execve_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->input_fd < 0 || cmd_exec_node->output_fd < 0)
		mini_exit_if_fd_neg(cmd_exec_node);
	if (cmd_exec_node->input_fd > 0)
	{
		dup2(cmd_exec_node->input_fd, STDIN_FILENO);
		close(cmd_exec_node->read_pipe);
		close(cmd_exec_node->input_fd);
	}
	else if (cmd_exec_node->input_fd == 0 && cmd_exec_node->read_pipe != -1)
	{
		dup2(cmd_exec_node->read_pipe, STDIN_FILENO);
		close(cmd_exec_node->read_pipe);
	}
	if (cmd_exec_node->output_fd > 1)
	{
		dup2(cmd_exec_node->output_fd, STDOUT_FILENO);
		close(cmd_exec_node->write_pipe);
		close(cmd_exec_node->output_fd);
	}
	else if (cmd_exec_node->output_fd == 1 && cmd_exec_node->write_pipe != -1)
	{
		dup2(cmd_exec_node->write_pipe, STDOUT_FILENO);
		close(cmd_exec_node->write_pipe);
	}
}

void	mini_exit_if_fd_neg(t_cmd *cmd_exec_node)
{
	mini_close_node_fd(cmd_exec_node);
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	exit(1);
}

void	command_not_found_handler(t_mini *mini, t_cmd *cmd_exec_node)
{
	if (ft_strchr(cmd_exec_node->cmd_path, '/')
		|| cmd_exec_node->cmd_path[0] == '.' || mini_is_path_unseted(mini))
		get_captalized_errors(mini, cmd_exec_node);
	else
	{
		ft_printf_fd(2, "%s: %s: %s\n", "minishell", cmd_exec_node->cmd_path,
			"command not found");
		mini->status = 127;
	}
}

void	get_captalized_errors(t_mini *mini, t_cmd *cmd_exec_node)
{
	int		status;
	char	*error_msg;

	if (access(cmd_exec_node->cmd_path, F_OK) < 0)
	{
		error_msg = "No such file or directory";
		status = 127;
	}
	else if (access(cmd_exec_node->cmd_path, X_OK) == 0)
	{
		error_msg = "Is a directory";
		status = 126;
	}
	else
	{
		error_msg = "Permission denied";
		status = 126;
	}
	ft_printf_fd(2, "%s: %s: %s\n", "minishell",
		cmd_exec_node->cmd_path, error_msg);
	mini->status = status;
}

static int	mini_is_path_unseted(t_mini *mini)
{
	t_dict	*cur;

	cur = mini->env_list;
	while (cur)
	{
		if (!ft_strncmp(cur->key, "PATH", ft_strlen(cur->key) + 4))
			return (0);
		cur = cur->next;
	}
	return (1);
}
