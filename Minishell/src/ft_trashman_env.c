/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trashman_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:59 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 20:09:33 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dictionary.h"
#include "../lib/includes/libft.h"
#include "../include/libftplus.h"
#include "../include/trashman.h"

t_list	**ft_get_mem_address_env(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	ft_collect_mem_env(void *content)
{
	ft_lstadd_back(ft_get_mem_address_env(), ft_lstnew(content));
}

void	ft_free_trashman_env(t_list **lst_memory)
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

t_dict	*ft_dictnew_env(char **var)
{
	t_dict	*new_entry;

	new_entry = malloc(sizeof(t_dict));
	if (new_entry == NULL)
		return (NULL);
	ft_collect_mem_env(new_entry);
	new_entry->key = var[0];
	new_entry->value = var[1];
	new_entry->next = NULL;
	return (new_entry);
}
