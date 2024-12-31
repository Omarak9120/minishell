/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:31:15 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 15:31:15 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//print_current_directory
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
