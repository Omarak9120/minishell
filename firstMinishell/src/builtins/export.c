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
    int has_value = parse_key_value(arg, key, value);  // Check if the arg has a value

    if (has_value)  // If it's a key-value pair
    {
        if (is_valid_identifier(key))
        {
            int i = 0;
            while (data->env[i] != NULL)
            {
                if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0 && 
                    (data->env[i][ft_strlen(key)] == '=' || data->env[i][ft_strlen(key)] == '\0'))
                {
                    // Update existing variable (whether it had value or not)
                    free(data->env[i]);
                    data->env[i] = malloc(strlen(key) + strlen(value) + 4);
                    if (data->env[i] == NULL)
                    {
                        ft_perror("Failed to allocate memory for environment variable");
                        return;
                    }
                    my_strcpy(data->env[i], key);
                    my_strcat(data->env[i], "=");
                    my_strcat(data->env[i], "\"");
                    my_strcat(data->env[i], value);
                    my_strcat(data->env[i], "\"");
                    return;
                }
                i++;
            }

            // Add the new variable as key=value
            size_t env_size = 0;
            while (data->env[env_size] != NULL) 
                env_size++;
            data->env = ft_realloc(data->env, sizeof(char *) * env_size, sizeof(char *) * (env_size + 2));
            if (data->env == NULL)
            {
                ft_perror("Failed to allocate memory");
                return;
            }
            data->env[env_size] = malloc(strlen(key) + strlen(value) + 4);
            if (data->env[env_size] == NULL)
            {
                ft_perror("Failed to allocate memory for environment variable");
                return;
            }
            my_strcpy(data->env[env_size], key);
            my_strcat(data->env[env_size], "=");
            my_strcat(data->env[env_size], "\"");
            my_strcat(data->env[env_size], value);
            my_strcat(data->env[env_size], "\"");
            data->env[env_size + 1] = NULL;
        }
        else
        {
            fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", key);
        }
    }
    else  // When there's no `=` in the argument (just a variable name)
    {
        if (is_valid_identifier(arg))
        {
            int i = 0;
            while (data->env[i] != NULL)
            {
                // Check if the variable already exists
                if (ft_strncmp(data->env[i], arg, ft_strlen(arg)) == 0 &&
                    (data->env[i][ft_strlen(arg)] == '=' || data->env[i][ft_strlen(arg)] == '\0'))
                {
                    return;  // Variable already exists, no need to add it again
                }
                i++;
            }

            // Add the variable without `=` if it doesn't exist
            size_t env_size = 0;
            while (data->env[env_size] != NULL) 
                env_size++;
            data->env = ft_realloc(data->env, sizeof(char *) * env_size, sizeof(char *) * (env_size + 2));
            if (data->env == NULL)
            {
                ft_perror("Failed to allocate memory");
                return;
            }
            data->env[env_size] = malloc(strlen(arg) + 1);  // Allocate space for key without '='
            if (data->env[env_size] == NULL)
            {
                ft_perror("Failed to allocate memory for environment variable");
                return;
            }
            my_strcpy(data->env[env_size], arg);  // Store just the key
            data->env[env_size + 1] = NULL;
        }
        else
        {
            fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", arg);
        }
    }
}


int compare_strings(const void *a, const void *b)
{
    const char **str1 = (const char **)a;
    const char **str2 = (const char **)b;
    return my_strcmp(*str1, *str2);
}

int builtin_export(t_data *data, char **args)
{
    if (args[1] == NULL)
    {
        int env_size = 0;
        while (data->env[env_size] != NULL)
            env_size++;
        qsort(data->env, env_size, sizeof(char *), compare_strings);
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
