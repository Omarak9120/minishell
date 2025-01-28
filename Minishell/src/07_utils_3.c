/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:30:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/18 11:49:27 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sub_token	*mini_sub_token_lstnew(char *content)
{
	t_sub_token	*new_node;

	new_node = malloc(sizeof(t_sub_token));
	ft_collect_mem(new_node);
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	mini_sub_token_lstadd_back(t_sub_token **lst, t_sub_token *new)
{
	t_sub_token	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_sub_token_lstlast(*lst);
	last_node->next = new;
}

t_sub_token	*mini_sub_token_lstlast(t_sub_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
