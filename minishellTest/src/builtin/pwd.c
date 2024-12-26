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
int	pwd_command(void)
{
	static char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Error retrieving current directory");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
