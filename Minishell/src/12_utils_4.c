/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:09:49 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 13:50:39 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

/**
 *   When executing a builtin in the parent or in a child,
 *   this function calls the corresponding builtin function, 
 *   storing the return status in mini->status.
 */

void	call_to_builtin(t_mini *mini, char *cmd, t_token *arg)
{
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 6))
		mini->status = export(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 4))
		mini->status = mini_echo(arg);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 3))
		mini->status = pwd();
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 2))
		mini->status = cd(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 3))
		mini->status = env(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 5))
		mini->status = unset(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 4))
	{
		mini_exit(arg, mini->status, mini);
	}
}

void	mini_backup_builtin_stdin(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
}

void	mini_set_builtin_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->input_fd > 0)
	{
		dup2(cmd_exec_node->input_fd, STDIN_FILENO);
		close(cmd_exec_node->read_pipe);
		close(cmd_exec_node->input_fd);
	}
	if (cmd_exec_node->output_fd > 1)
	{
		dup2(cmd_exec_node->output_fd, STDOUT_FILENO);
		close(cmd_exec_node->write_pipe);
		close(cmd_exec_node->output_fd);
	}
}

void	mini_restore_builtin_fd(int *stdin_backup, int *stdout_backup)
{
	dup2(*stdin_backup, STDIN_FILENO);
	dup2(*stdout_backup, STDOUT_FILENO);
	close(*stdin_backup);
	close(*stdout_backup);
}
