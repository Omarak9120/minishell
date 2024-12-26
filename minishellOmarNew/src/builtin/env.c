/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:12:30 by odib              #+#    #+#             */
/*   Updated: 2024/09/04 13:42:37 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_command(t_env *env_list)
{
	t_env	*temp;

	if (env_list == NULL)
	{
		perror("Error: Environment list is NULL\n");
		return (1);
	}
	temp = env_list;
	while (temp != NULL)
	{
		if (temp->hidden == 0)
			printf("%s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
	free_env_list(temp);
	return (0);
}
