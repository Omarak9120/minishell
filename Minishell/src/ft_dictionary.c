/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictionary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:26:06 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/19 17:04:08 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dictionary.h"
#include "../lib/includes/libft.h"
#include "../include/libftplus.h"
#include "../include/trashman.h"

void	ft_dict_insert(t_dict **dict, char **var)
{
	if (1)
	{
		if (!ft_dict_update(*dict, var))
			ft_dictadd_back(dict, ft_dictnew(var));
	}
}

t_dict	*ft_dictnew(char **var)
{
	t_dict	*new_entry;

	new_entry = malloc(sizeof(t_dict));
	if (new_entry == NULL)
		return (NULL);
	ft_collect_mem(new_entry);
	new_entry->key = var[0];
	new_entry->value = var[1];
	new_entry->next = NULL;
	return (new_entry);
}

void	ft_dictadd_back(t_dict **dict, t_dict *new_entry)
{
	t_dict	*last_node;

	if (*dict == NULL)
	{
		*dict = new_entry;
		return ;
	}
	last_node = ft_dictlast(*dict);
	last_node->next = new_entry;
}

t_dict	*ft_dictlast(t_dict *dict)
{
	if (dict == NULL)
		return (NULL);
	while (dict->next != NULL)
		dict = dict->next;
	return (dict);
}

int	ft_dict_update(t_dict *dict, char **var)
{
	t_dict	*cur;

	cur = dict;
	while (cur)
	{
		if (!ft_strncmp(cur->key, var[0], ft_strlen(var[0])))
		{
			if (var[1])
				cur->value = var[1];
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
