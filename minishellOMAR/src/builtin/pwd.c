/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:09:41 by odib              #+#    #+#             */
/*   Updated: 2024/12/31 11:31:21 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_command(t_env *env_list)
{
	static char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		int nbr = env_list->two_point;
		char *pwd;
		int i = 0;
		pwd = get_env(env_list, "PWD");
		printf("%s", pwd);
		while (i < nbr)
		{
			printf("/..");
			i++;
		}
		printf("\n");
		return (1);
	}
}
