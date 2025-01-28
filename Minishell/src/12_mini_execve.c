/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_mini_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:23:06 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/19 11:26:40 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include "../include/builtins.h"

void	mini_execve(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	t_token	*token_lst;
	int		i;
	int		is_simple_cmd;
	int		is_builtin;

	cmd_exec_node = mini->cmd_exec_list;
	is_simple_cmd = mini_is_simple_cmd(cmd_exec_node);
	i = 0;
	while (cmd_exec_node)
	{
		token_lst = mini_exec_interface(cmd_exec_node->cmd_exec);
		is_builtin = mini_is_builtin(token_lst);
		if (is_simple_cmd && is_builtin)
			mini_exec_builtin(token_lst, mini, cmd_exec_node);
		else
			mini_exec_fork(mini, cmd_exec_node, token_lst);
		cmd_exec_node = cmd_exec_node->next;
		i++;
	}
	mini_close_all_fd(mini);
	mini_wait_childs(mini);
}

void	mini_exec_fork(t_mini *mini,
	t_cmd *cmd_exec_node, t_token *token_node)
{
	mini->int_action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &mini->int_action, NULL);
	cmd_exec_node->pid = fork();
	if (cmd_exec_node->pid == 0)
		mini_execve_child(mini, cmd_exec_node, token_node);
}

void	mini_execve_child(t_mini *mini,
	t_cmd *cmd_exec_node, t_token *token_node)
{
	mini->int_action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &mini->int_action, NULL);
	mini->quit_action.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &mini->quit_action, NULL);
	mini_close_pipes(mini, cmd_exec_node);
	mini_manage_execve_fd(cmd_exec_node);
	if (cmd_exec_node->cmd_path && !mini_cmd_selection(token_node, mini))
	{
		execve(cmd_exec_node->cmd_path,
			cmd_exec_node->cmd_exec, mini->mini_environ);
		command_not_found_handler(mini, cmd_exec_node);
	}
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	exit(mini->status);
}

void	mini_wait_childs(t_mini *mini)
{
	int		status;
	t_cmd	*cmd_exec_node;

	status = 0;
	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		waitpid(cmd_exec_node->pid, &status, 0);
		mini_get_status(mini, status);
		cmd_exec_node = cmd_exec_node->next;
	}
}

void	mini_get_status(t_mini *mini, int status)
{
	if (WIFEXITED(status))
		mini->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		printf("\n");
		if (WTERMSIG(status) == SIGQUIT)
			mini->status = 131;
		else if (WTERMSIG(status) == SIGINT)
			mini->status = 130;
	}
}
