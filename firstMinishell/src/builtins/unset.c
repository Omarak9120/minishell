/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:28:41 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/14 20:28:41 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int unset_env_variable(t_data *data, const char *var_name)
{
    int i = 0;
    int len = ft_strlen(var_name);

    while (data->env[i] != NULL)
    {
        // Check if the current environment variable starts with the var_name
        if (ft_strncmp(data->env[i], var_name, len) == 0 && (data->env[i][len] == '=' || data->env[i][len] == '\0'))
        {
            free(data->env[i]);

            // Shift remaining elements left
            while (data->env[i] != NULL)
            {
                data->env[i] = data->env[i + 1];
                i++;
            }
            return 0; // Successfully removed
        }
        i++;
    }
    return 1; // Variable not found
}


int builtin_unset(t_data *data, char **args)
{
    int i = 1;
    
    if (args[1] == NULL)
    {
        fprintf(stderr, "minishell: unset: not enough arguments\n");
        data->exit_status = 1;
        return 1;
    }
    while (args[i])
    {
        if (unset_env_variable(data, args[i]) != 0)
            fprintf(stderr, "minishell: unset: %s: not found\n", args[i]);
        i++;
    }

    return 0;
}

