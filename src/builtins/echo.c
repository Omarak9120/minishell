/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:17:54 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/28 17:15:10 by mjamil           ###   ########.fr       */
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

void expand_variables(t_data *data, const char *arg, char *buffer)
{
    int i = 0, j = 0;
    bool in_single_quotes = false;
    bool in_double_quotes = false;

    while (arg[i] != '\0')
    {
        if (arg[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;  // Toggle single quotes
            i++;
        }
        else if (arg[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;  // Toggle double quotes
            i++;
        }
        else if (arg[i] == '$')
        {
            if (in_single_quotes)
            {
                // If in single quotes, treat $ as literal
                buffer[j++] = arg[i++];
            }
            else if (arg[i + 1] == '$')
            {
                // Handle $$ for process ID
                char pid_str[16];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                my_strcpy(&buffer[j], pid_str);
                j += ft_strlen(pid_str);
                i += 2;
            }
            else if (arg[i + 1] == '?')
            {
                // Handle $? for last exit status
                char exit_status_str[16];
                snprintf(exit_status_str, sizeof(exit_status_str), "%d", data->exit_status);
                my_strcpy(&buffer[j], exit_status_str);
                j += ft_strlen(exit_status_str);
                i += 2;
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
                // Do not add anything if the variable is not found
            }
        }
        else
        {
            // Normal characters
            buffer[j++] = arg[i++];
        }
    }
    buffer[j] = '\0';  // Null-terminate the buffer
}


// Function to remove quotes and expand variables where needed
void process_echo_argument(t_data *data, const char *arg, char *buffer)
{
    int i = 0, j = 0;
    bool in_single_quotes = false, in_double_quotes = false;

    while (arg[i] != '\0')
    {
        if (arg[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;  // Toggle single quotes
            i++;
        }
        else if (arg[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;  // Toggle double quotes
            i++;
        }
        else if (arg[i] == '$' && in_double_quotes && !in_single_quotes)
        {
            // Expand environment variables within double quotes
            char expanded[1024] = "";
            expand_variables(data, (char *)&arg[i], expanded);

            // Copy expanded variable content into buffer
            my_strcpy(&buffer[j], expanded);
            j += strlen(expanded);

            // Skip over the variable name in the original string
            while (arg[i + 1] && (ft_isalnum(arg[i + 1]) || arg[i + 1] == '_'))
            {
                i++;
            }
            i++;  // Skip past the variable

            // Ensure no quotes are accidentally added after the variable
            if (arg[i] == '"')
            {
                in_double_quotes = false;  // Close the double quote if we reach it
                i++;
            }
        }
        else
        {
            // Normal characters
            buffer[j++] = arg[i++];
        }
    }
    buffer[j] = '\0';  // Null-terminate the buffer
}

// Echo function to print the message
void echo(const char *message, bool no_newline) {
    printf("%s", message);
    if (!no_newline) printf("\n");
}

// The main builtin echo function
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