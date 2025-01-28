/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trashman_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:44:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/19 11:34:14 by josfelip         ###   ########.fr       */
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
