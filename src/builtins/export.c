/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:11 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/14 19:47:11 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

extern char **environ;

int parse_key_value(const char *arg, char *key, char *value)
{
    char *equal_sign = strchr(arg, '=');

    // If no equal sign is found, this is not a valid export argument
    if (!equal_sign)
        return 0;

    // Copy the key (part before the equal sign)
    strncpy(key, arg, equal_sign - arg);
    key[equal_sign - arg] = '\0';  // Null-terminate the key

    // Copy the value (part after the equal sign)
    strcpy(value, equal_sign + 1);
    return 1;
}

int builtin_export(t_data *data, char **args)
{
    (void)data;  // Currently unused, but can be used for shell state

    if (args[1] == NULL)
    {
        // If no arguments, print all environment variables
        extern char **environ;
        for (char **env = environ; *env != NULL; env++)
        {
            printf("declare -x %s\n", *env);
        }
        return 0;
    }

    // Process all the provided arguments
    for (int i = 1; args[i]; i++)
    {
        char key[1024] = {0};
        char value[1024] = {0};

        // Parse the argument into a key=value pair
        if (!parse_key_value(args[i], key, value))
        {
            fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);
            continue;
        }

        // Set the environment variable
        if (setenv(key, value, 1) == -1)
        {
            perror("minishell: export");
            return 1;
        }
    }

    return 0;
}
