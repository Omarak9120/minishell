/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_mini_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:09:19 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:09:20 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include "../include/builtins.h"

/*	 1) Convert its cmd_exec array to a token list (mini_exec_interface).
 *   2) Check if it's a builtin (mini_is_builtin).
 *   3) If there's only one command and it's builtin, execute in the parent 
 *      (mini_exec_builtin); otherwise, fork and run in a child (mini_exec_fork).
 *   After all commands are launched, close any remaining file descriptors 
 *   and wait for the child processes (mini_wait_childs), which updates $?.*/

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
/**
 *   Forks a new process for the given command node. In the parent, 
 *   sets SIGINT to be ignored so Ctrl+C won't kill the shell but 
 *   only the child if needed. The child process is handed off to 
 *   mini_execve_child.
 */

void	mini_exec_fork(t_mini *mini,
	t_cmd *cmd_exec_node, t_token *token_node)
{
	mini->int_action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &mini->int_action, NULL);
	cmd_exec_node->pid = fork();
	if (cmd_exec_node->pid == 0)
		mini_execve_child(mini, cmd_exec_node, token_node);
}
/**
 *   The child process logic after fork. Restores default signal handling 
 *   (so Ctrl+C can terminate the child), closes irrelevant pipes, and 
 *   duplicates file descriptors for redirection/piping (mini_manage_execve_fd).
 *   Then checks if it's a builtin (mini_cmd_selection) or an external command 
 *   (execve). If execve fails, handle "command not found". Frees all allocated 
 *   memory and exits with mini->status.
 */

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
/**
 *   Waits on every child process (t_cmd->pid). 
 *   For each completed child, retrieves its exit code or signal-based 
 *   termination with waitpid, then updates mini->status via 
 *   mini_get_status (so $? is accurate).
 */

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
/**
 *   Interprets the wait status to set mini->status. If the child 
 *   exited normally, mini->status = its exit code (WEXITSTATUS). 
 *   If it was killed by a signal, print a newline and set 
 *   mini->status to 130 (SIGINT) or 131 (SIGQUIT), etc.
 */

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
