/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:49:08 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/19 16:51:34 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

void	mini_exec_builtin(t_token *token_lst,
		t_mini *mini, t_cmd *cmd_exec_node)
{
	char	*cmd;
	t_token	*arg;
	int		stdin_backup;
	int		stdout_backup;

	if (cmd_exec_node->input_fd < 0 || cmd_exec_node->output_fd < 0)
		return ;
	mini_backup_builtin_stdin(&stdin_backup, &stdout_backup);
	mini_set_builtin_fd(cmd_exec_node);
	cmd = token_lst->token;
	arg = token_lst->next;
	mini_call_to_builtin(mini, cmd, arg);
	mini_restore_builtin_fd(&stdin_backup, &stdout_backup);
}

int	mini_is_simple_cmd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->next)
		return (0);
	return (1);
}

t_token	*mini_exec_interface(char **cmd_exec)
{
	t_token	*token_lst;
	int		i;

	token_lst = NULL;
	i = 0;
	while (cmd_exec && cmd_exec[i])
		mini_token_lstadd_back(&token_lst, mini_token_lstnew(cmd_exec[i++], 0));
	return (token_lst);
}

int	mini_is_builtin(t_token *token_lst)
{
	char	*cmd;
	int		is_builtin;

	is_builtin = 0;
	if (!token_lst)
		return (is_builtin);
	cmd = token_lst->token;
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 6))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 4))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 3))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 2))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 3))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 5))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 4))
		is_builtin = 1;
	return (is_builtin);
}

int	mini_cmd_selection(t_token *token_lst, t_mini *mini)
{
	char	*cmd;
	t_token	*arg;
	int		executed;

	cmd = token_lst->token;
	arg = token_lst->next;
	executed = 1;
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 6))
		mini->status = mini_export(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 4))
		mini->status = mini_echo(arg);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 3))
		mini->status = mini_pwd();
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 2))
		mini->status = mini_cd(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 3))
		mini->status = mini_env(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 5))
		mini->status = mini_unset(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 4))
		mini_exit(arg, mini->status);
	else
		executed = 0;
	return (executed);
}
