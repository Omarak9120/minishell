/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trashman.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:04 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 20:22:21 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/trashman.h"

/*Why Static? The pointer persists between function calls,
 ensuring all memory references remain accessible.*/

t_list	**ft_get_mem_addresss(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	ft_collect_mem(void *content)
{
	ft_lstadd_back(ft_get_mem_addresss(), ft_lstnew(content));
}

void	ft_trashman(t_list **lst_memory)
{
	t_list	*next;

	while (*lst_memory)
	{
		next = (*lst_memory)->next;
		free((*lst_memory)->content);
		free(*lst_memory);
		*lst_memory = next;
	}
	*lst_memory = NULL;
}
