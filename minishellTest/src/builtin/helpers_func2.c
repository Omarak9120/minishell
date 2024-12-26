/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:18:27 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 16:18:27 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//swap_env_nodes
void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;
	int		temphidden;

	temp_key = a->key;
	temp_value = a->value;
	temphidden = a->hidden;
	a->hidden = b->hidden;
	a->key = b->key;
	a->value = b->value;
	b->hidden = temphidden;
	b->key = temp_key;
	b->value = temp_value;
}

//sort_environment_variables
void	sort_env_list(t_env *head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (head == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

//strip_quotes
void	remove_quotes_from_str(char *str)
{
	char	*src;
	char	*dst;
	char	quote;

	quote = 0;
	src = str;
	dst = str;
	while (*src)
	{
		if (!quote && (*src == '\'' || *src == '\"'))
			quote = *src;
		else if (quote && *src == quote)
			quote = 0;
		else
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
	free(src);
	free(dst);
}

//is_valid_key
int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		return (0);
	}
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

//display_sorted_env_variables
void	print_sorted_env_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->value == NULL)
			printf("%s\n", current->key);
		else
			printf("%s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
	free_env_list(current);
}
