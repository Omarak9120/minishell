/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:08:20 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:08:23 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_free_token_list(t_token **lst_memory)
{
	t_token	*next;

	while (*lst_memory)
	{
		next = (*lst_memory)->next;
		free((*lst_memory)->token);
		free(*lst_memory);
		*lst_memory = next;
	}
	*lst_memory = NULL;
}

void	mini_lstdelone(t_token *lst)
{
	if (lst && lst->token)
	{
		free(lst->token);
		free(lst);
	}
}
// void	debug_print_split(char **str)
// {
// 	while (*str)
// 	{
// 		printf("%s | ", *str);
// 		str++;
// 	}
// 	printf("\n");
// }

// void	debug_print_list(t_token **head)
// {
// 	t_token	*node;

// 	node = *head;
// 	while (node)
// 	{
// 		printf("token: %s\n", (char *)node->token);
// 		node = node->next;
// 	}
// 	printf("\n");
// }
