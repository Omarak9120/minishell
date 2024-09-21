/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:56:09 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/21 12:56:35 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *my_getenv(char **env, const char *name)
{
    size_t len = strlen(name);

    for (int i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return &env[i][len + 1];
    }
    return NULL;
}
