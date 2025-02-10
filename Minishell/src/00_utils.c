/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:43 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/10 20:03:01 by oabdelka         ###   ########.fr       */
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

void	ctrl_d_exit(void)
{
	printf("exit\n");
	clear_history();
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
