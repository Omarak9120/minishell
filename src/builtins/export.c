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

int parse_key_value(const char *arg, char *key, char *value)
{
    char *equal_sign = ft_strchr(arg, '=');

    if (!equal_sign)
        return 0;
    my_strncpy(key, arg, equal_sign - arg);
    key[equal_sign - arg] = '\0';

    my_strcpy(value, equal_sign + 1);
    return 1;
}

int builtin_export(t_data *data, char **args)
{
    (void)data;

    if (args[1] == NULL)
    {
        extern char **environ;
        for (char **env = environ; *env != NULL; env++)
        {
            printf("declare -x %s\n", *env);
        }
        return 0;
    }
    int i = 1;
    while (args[i])
    {
        char key[1024] = {0};
        char value[1024] = {0};

        if (!parse_key_value(args[i], key, value))
        {
            fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);
            continue;
        }

        if (setenv(key, value, 1) == -1)
        {
            perror("minishell: export");
            return 1;
        }
        i++;
    }

    return 0;
}
