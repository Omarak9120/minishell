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

int is_valid_identifier(const char *key);
void add_env_variable(t_data *data, const char *arg);

int parse_key_value(const char *arg, char *key, char *value)
{
    char *equal_sign = strchr(arg, '=');
    if (!equal_sign)
        return 0;
    my_strncpy(key, arg, equal_sign - arg);
    key[equal_sign - arg] = '\0';
    my_strcpy(value, equal_sign + 1);
    return 1;
}

void add_env_variable(t_data *data, const char *arg)
{
    char key[1024] = {0};
    char value[1024] = {0};

    if (parse_key_value(arg, key, value))
    {
        if (is_valid_identifier(key))
        {
            int i = 0;
            while (data->env[i] != NULL)
            {
                if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0 && data->env[i][ft_strlen(key)] == '=')
                {
                    free(data->env[i]);
                    data->env[i] = malloc(strlen(arg) + 1);
                    if (data->env[i] == NULL)
                    {
                        ft_perror("Failed to allocate memory for environment variable");
                        return;
                    }
                    my_strcpy(data->env[i], arg);
                    return;
                }
                i++;
            }

            size_t env_size = 0;
            while (data->env[env_size] != NULL) 
                env_size++;
            data->env = ft_realloc(data->env, sizeof(char *) * env_size, sizeof(char *) * (env_size + 2));
            if (data->env == NULL)
            {
                ft_perror("Failed to allocate memory");
                return;
            }
            data->env[env_size] = malloc(strlen(arg) + 1);
            if (data->env[env_size] == NULL)
            {
                ft_perror("Failed to allocate memory for environment variable");
                return;
            }
            my_strcpy(data->env[env_size], arg);
            data->env[env_size + 1] = NULL;
        }
        else
            fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", key);
    }
    else
    {
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", arg);
    }
}


int builtin_export(t_data *data, char **args)
{
    if (args[1] == NULL)
    {
        int i = 0;
        while (data->env[i] != NULL)
        {
            printf("declare -x %s\n", data->env[i]);
            i++;
        }
        return 0;
    }

    int i = 1;
    while (args[i])
    {
        add_env_variable(data, args[i]);
        i++;
    }
    return 0;
}

int is_valid_identifier(const char *key)
{
    if (!ft_isalpha(key[0]) && key[0] != '_')
        return 0;
    int i = 1;
    while (key[i] != '\0') 
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return 0;
        i++;
    }
    return 1;
}
