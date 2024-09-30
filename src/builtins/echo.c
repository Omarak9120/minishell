/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:17:54 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/30 22:03:14 by mjamil           ###   ########.fr       */
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

void expand_variables(t_data *data, const char *arg, char *buffer) {
    int i = 0, j = 0;
    bool in_single_quotes = false;
    bool in_double_quotes = false;

    while (arg[i] != '\0') {
        if (arg[i] == '\'' && !in_double_quotes) {
            in_single_quotes = !in_single_quotes;
            i++;
        } else if (arg[i] == '"' && !in_single_quotes) {
            in_double_quotes = !in_double_quotes;
            i++;
        } else if (arg[i] == '$') {
            if (in_single_quotes) {
                buffer[j++] = arg[i++];
            } else if (arg[i + 1] == '$') {
                // Handle $$ for process ID
                char pid_str[16];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                my_strcpy(&buffer[j], pid_str);
                j += ft_strlen(pid_str);
                i += 2;
            } else if (arg[i + 1] == '?') {
                // Handle $? for last exit status
                char status_str[16];
                snprintf(status_str, sizeof(status_str), "%d", data->exit_status);
                my_strcpy(&buffer[j], status_str);
                j += ft_strlen(status_str);
                i += 2; // Skip past the '?'
            } else if (arg[i + 1] == '\0' || !ft_isalnum(arg[i + 1])) {
                buffer[j++] = '$';
                i++;
            } else if (ft_isdigit(arg[i + 1])) {
                // Handle $ followed by a number: remove first digit
                i++;  // Skip the $
                i++;  // Skip the first digit
                while (ft_isdigit(arg[i])) {
                    buffer[j++] = arg[i++];
                }
            } else if (ft_isalpha(arg[i + 1])) {
                // Handle $ followed by alphabetic string: retrieve the environment variable
                i++;  // Skip the $
                char var_name[128];
                int var_len = 0;

                // Extract variable name
                while (arg[i] != '\0' && (ft_isalnum(arg[i]) || arg[i] == '_')) {
                    var_name[var_len++] = arg[i++];
                }
                var_name[var_len] = '\0';

                // Check for environment variable
                char *env_value = my_getenv(data->env, var_name);
                if (env_value) {
                    my_strcpy(&buffer[j], env_value);
                    j += ft_strlen(env_value);
                }
            } else {
                buffer[j++] = '$';
                i++;
            }
        } else {
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
void strip_quotes(char *str)
{
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"')
    {
        str[len - 1] = '\0'; // Remove ending quote
        memmove(str, str + 1, len - 1); // Remove starting quote
    }
}

int builtin_echo(t_data *data, char **args)
{
    if (args[0] && my_strcmp(args[0], "echo") == 0)
    {
        bool no_newline = false;
        int i = 1;

        // Check for -n flag (to avoid printing newline)
        while (args[i] && is_n_flag(args[i]))
        {
            no_newline = true;
            i++;
        }

        char message[1024] = "";
        bool first_word = true;

        while (args[i])
        {
            char expanded[1024] = "";
            expand_variables(data, args[i], expanded);

            // Strip quotes from the expanded variable
            strip_quotes(expanded);

            // Only add a space if this is not the first word
            if (!first_word && expanded[0] != '\0')
                my_strcat(message, " ");

            // Append the expanded variable or word to the message
            my_strcat(message, expanded);

            if (expanded[0] != '\0')
                first_word = false;

            i++;
        }

        // Print the final message
        echo(message, no_newline);
    }
    else
    {
        write(1, "\n", 1);
    }

    return 0;
}

