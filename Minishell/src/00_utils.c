/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:23:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 14:26:57 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_mini	*get_mini_address(void)
{
	static t_mini	mini;

	return (&mini);
}

void	mini_init(t_mini *mini)
{
	mini->path = NULL;
	mini->lst_memory = NULL;
	mini->cmd_line = NULL;
	mini->pathname = NULL;
	mini->token_list = NULL;
	mini->cmd_exec_list = NULL;
	mini->syntax_error = 0;
	mini->mini_environ = NULL;
	mini->hd_file_index = 0;
}

void	mini_trashman_collector(t_list **list_memory, void *trash)
{
	if (list_memory)
		ft_lstadd_back(list_memory, ft_lstnew(trash));
	else
		*list_memory = ft_lstnew(trash);
}

void	mini_ctrl_d_exit(void)
{
	printf("exit\n");
	clear_history();
}
