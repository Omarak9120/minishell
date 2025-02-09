/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:43 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 16:41:08 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_mini	*get_address(void)
{
	static t_mini	mini;

	return (&mini);
}

void	init(t_mini *mini)
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

// void	mini_trashman_collector(t_list **list_memory, void *trash)
// {
// 	if (list_memory)
// 		ft_lstadd_back(list_memory, ft_lstnew(trash));
// 	else
// 		*list_memory = ft_lstnew(trash);
// }

void	ctrl_D_exit(void)
{
	printf("exit\n");
	clear_history();
}
