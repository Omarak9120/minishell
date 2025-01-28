/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:30:59 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 13:25:10 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*mini_redir_lstnew(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (new_node == NULL)
		return (NULL);
	new_node->input_fd = 0;
	new_node->output_fd = 1;
	new_node->read_pipe = -1;
	new_node->write_pipe = -1;
	new_node->nbr_of_words = 0;
	new_node->cmd_exec = NULL;
	new_node->cmd_path = NULL;
	new_node->next = NULL;
	new_node->pid = -1;
	ft_collect_mem(new_node);
	return (new_node);
}

void	mini_redir_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_redir_lstlast(*lst);
	last_node->next = new;
}

t_cmd	*mini_redir_lstlast(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
