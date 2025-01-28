/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictionary_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:44:30 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/17 12:26:39 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dictionary.h"

void	ft_dict_print(t_dict *dict)
{
	t_dict	*cur;

	cur = dict;
	while (cur)
	{
		if (cur->value)
			ft_printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			ft_printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
}

t_dict	*ft_dictsort(t_dict *dict)
{
	t_dict	*header;
	char	*key;
	char	*value;
	size_t	len;

	header = dict;
	len = ft_max(ft_strlen(dict->key), ft_strlen(dict->next->key));
	while (dict->next)
	{
		if (ft_strncmp(dict->key, dict->next->key, len) <= 0)
			dict = dict->next;
		else
		{
			key = dict->key;
			value = dict->value;
			dict->key = dict->next->key;
			dict->value = dict->next->value;
			dict->next->key = key;
			dict->next->value = value;
			dict = header;
		}
	}
	return (header);
}

size_t	ft_max(size_t a, size_t b)
{
	size_t	max;

	max = a;
	if (max < b)
		max = b;
	return (max);
}

int	ft_dictdel_entry(t_dict **dict, char *name)
{
	t_dict	*cur;
	t_dict	*prev;

	cur = *dict;
	prev = NULL;
	while (cur)
	{
		if (!ft_strncmp(cur->key, name, ft_strlen(name)))
		{
			if (prev)
				prev->next = cur->next;
			else
				*dict = cur->next;
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

char	*ft_dict_get_value(t_dict *dict, char *key)
{
	char	*value;

	value = NULL;
	while (dict->key)
	{
		if (!ft_strncmp(dict->key, key, ft_strlen(key)))
		{
			value = dict->value;
			break ;
		}
		dict = dict->next;
	}
	return (value);
}
