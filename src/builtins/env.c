/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:31:24 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/14 20:31:24 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int builtin_env(t_data *data, char **args)
{
    // Check if there are any extra arguments
    if (args[1] != NULL) {
        fprintf(stderr, "env: '%s': No such file or directory\n", args[1]);
        return (127); // Standard error code for command not found
    }

    // Check if data or environment is null
    if (data == NULL || data->env == NULL) {
        printf("Error: No environment context available.\n");
        return (1); // Error code for failure
    }

    // Use the environment variables from the struct
    char **env = data->env;

    // Iterate through the environment variables and print each one
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    return (0); // Success
}