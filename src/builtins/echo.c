/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:17:54 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/27 14:44:34 by oabdelka         ###   ########.fr       */
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

// void expand_variables(t_data *data, char *arg, char *buffer)
// {
//     int i = 0, j = 0;

//     while (arg[i] != '\0')
//     {
//         if (arg[i] == '$')
//         {
//             if (arg[i + 1] == '$')
//             {
//                 // Replace $$ with the process ID
//                 char pid_str[16];
//                 snprintf(pid_str, sizeof(pid_str), "%d", getpid());
//                 my_strcpy(&buffer[j], pid_str);
//                 j += ft_strlen(pid_str);
//                 i += 2;
//             }
//             else if (arg[i + 1] == '?')
//             {
//                 // Replace $? with the last exit status
//                 char exit_status_str[16];
//                 snprintf(exit_status_str, sizeof(exit_status_str), "%d", data->exit_status);
//                 my_strcpy(&buffer[j], exit_status_str);
//                 j += ft_strlen(exit_status_str);
//                 i += 2;
//             }
//             else
//             {
//                 i++;
//                 char var_name[128];
//                 int var_len = 0;

//                 // Capture the variable name
//                 while (arg[i] != '\0' && (ft_isalnum(arg[i]) || arg[i] == '_'))
//                 {
//                     var_name[var_len++] = arg[i++];
//                 }
//                 var_name[var_len] = '\0';

//                 // Fetch the variable's value from the environment
//                 char *env_value = my_getenv(data->env, var_name);
//                 if (env_value)
//                 {
//                     my_strcpy(&buffer[j], env_value);
//                     j += ft_strlen(env_value);
//                 }
//             }
//         }
//         else
//         {
//             // Normal characters
//             buffer[j++] = arg[i++];
//         }
//     }
//     buffer[j] = '\0'; // Null-terminate the buffer
// }

void expand_variables(t_data *data, char *arg, char *buffer)
{
    int i = 0, j = 0;

    while (arg[i] != '\0')
    {
        if (arg[i] == '$')
        {
            if (arg[i + 1] == '$')
            {
                // Handle $$
                char pid_str[16];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                my_strcpy(&buffer[j], pid_str);
                j += ft_strlen(pid_str);
                i += 2;
            }
            else if (arg[i + 1] == '?')
            {
                // Handle $?
                char exit_status_str[16];
                snprintf(exit_status_str, sizeof(exit_status_str), "%d", data->exit_status);
                my_strcpy(&buffer[j], exit_status_str);
                j += ft_strlen(exit_status_str);
                i += 2;
            }
            else if (arg[i + 1] == '\0' || !ft_isalnum(arg[i + 1]))
            {
                // Handle $ without a valid variable name (treat it as literal '$')
                buffer[j++] = '$';
                i++;
            }
            else
            {
                i++;
                char var_name[128];
                int var_len = 0;

                // Capture the variable name
                while (arg[i] != '\0' && (ft_isalnum(arg[i]) || arg[i] == '_'))
                {
                    var_name[var_len++] = arg[i++];
                }
                var_name[var_len] = '\0';

                // Fetch the variable's value from the environment
                char *env_value = my_getenv(data->env, var_name);
                if (env_value)
                {
                    my_strcpy(&buffer[j], env_value);
                    j += ft_strlen(env_value);
                }
                else
                {
                    // If the variable is not found, output an empty string or handle as needed
                    buffer[j++] = '$'; // Optionally, keep the $ in the output if the variable is not found
                }
            }
        }
        else
        {
            // Normal characters
            buffer[j++] = arg[i++];
        }
    }
    buffer[j] = '\0'; // Null-terminate the buffer
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