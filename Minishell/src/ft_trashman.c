/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trashman.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:44:33 by gfantoni          #+#    #+#             */
/*   Updated: 2025/01/22 17:25:40 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/trashman.h"

t_list	**ft_get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

/*Register it in the trash collector */
void	ft_collect_mem(void *content)
{
	ft_lstadd_back(ft_get_mem_address(), ft_lstnew(content));
}

void	ft_free_trashman(t_list **lst_memory)
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
