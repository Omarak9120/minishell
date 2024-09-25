/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:17:54 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/23 14:20:03 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_n_flag(const char *arg)
{
    if (arg[0] == '-')
    {
        int i = 1;
        while (arg[i] != '\0')
        {
            if (arg[i] != 'n')
                return false;
            i++;
        }
        return true;
    }
    return false;
}

void expand_variables(t_data *data, char *arg, char *buffer)
{
    int i = 0, j = 0;

    while (arg[i] != '\0')
    {
        if (arg[i] == '$')
        {
            if (arg[i + 1] == '$')
            {
                char pid_str[16];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                my_strcpy(&buffer[j], pid_str);
                j += ft_strlen(pid_str);
                i += 2;
            }
            else if (arg[i + 1] == '$' && arg[i + 2] == '$')
            {
                char parent_pid_str[16];
                snprintf(parent_pid_str, sizeof(parent_pid_str), "%d", getppid());
                my_strcpy(&buffer[j], parent_pid_str);
                j += ft_strlen(parent_pid_str);
                i += 3;
            }
            else if (arg[i + 1] == '?')
            {
                my_strcpy(&buffer[j], "0");
                j += 1;
                i += 2;
            }
            else
            {
                i++;
                char var_name[128];
                int var_len = 0;

                while (arg[i] != '\0' && (ft_isalnum(arg[i]) || arg[i] == '_'))
                    var_name[var_len++] = arg[i++];
                var_name[var_len] = '\0';
                char *default_value = NULL;
                if (arg[i] == ':')
                {
                    i++;
                    if (arg[i] == '-')
                    {
                        i++;
                        char default_name[128];
                        int def_len = 0;
                        while (arg[i] != '\0' && (ft_isalnum(arg[i]) || arg[i] == '_'))
                            default_name[def_len++] = arg[i++];
                        default_name[def_len] = '\0';
                        default_value = default_name;
                    }
                }

                char *env_value = my_getenv(data->env, var_name);
                if (env_value)
                {
                    if (env_value[0] == '"' && env_value[strlen(env_value) - 1] == '"')
                    {
                        my_strncpy(&buffer[j], env_value + 1, strlen(env_value) - 2);
                        j += strlen(env_value) - 2;
                    }
                    else
                    {
                        my_strcpy(&buffer[j], env_value);
                        j += ft_strlen(env_value);
                    }
                }
                else if (default_value)
                {
                    my_strcpy(&buffer[j], default_value);
                    j += ft_strlen(default_value);
                }
            }
        }
        else
        {
            buffer[j++] = arg[i++];
        }
    }
    buffer[j] = '\0';
}


void echo(const char *message, bool no_newline)
{
    printf("%s", message);
    if (!no_newline)
        printf("\n");
}

int builtin_echo(t_data *data, char **args)
{
    if (args[0] && my_strcmp(args[0], "echo") == 0)
    {
        bool no_newline = false;
        int i = 1;
        while (args[i] && is_n_flag(args[i]))
        {
            no_newline = true;
            i++;
        }
        char message[1024] = "";
        bool first_word = true;
        while (args[i])
        {
            if (!first_word)
                my_strcat(message, " ");
            char expanded[1024] = "";
            expand_variables(data, args[i], expanded);
            
            my_strcat(message, expanded);
            first_word = false;
            i++;
        }
        echo(message, no_newline);
    }
    else
        write(1, "\n", 1);

    return 0;
}