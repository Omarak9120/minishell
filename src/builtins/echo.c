#include "../../includes/minishell.h"


bool is_n_flag(const char *arg)
{
    if (arg[0] == '-')
    {
        for (int i = 1; arg[i] != '\0'; i++)
        {
            if (arg[i] != 'n')
                return false;
        }
        return true;
    }
    return false;
}

void expand_variables(char *arg, char *buffer)
{
    int i = 0, j = 0;

    while (arg[i] != '\0')
    {
        if (arg[i] == '$')
        {
            // If there's only a single '$', just print it
            if (arg[i + 1] == '\0')
            {
                buffer[j++] = '$';
                i++;
            }
            // If $$, output the PID of the current process
            else if (arg[i + 1] == '$')
            {
                char pid_str[16];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                strcpy(&buffer[j], pid_str);
                j += strlen(pid_str);
                i += 2; // Skip the $$
            }
            // If $$$, output the PID of the parent process
            else if (arg[i + 1] == '$' && arg[i + 2] == '$')
            {
                char parent_pid_str[16];
                snprintf(parent_pid_str, sizeof(parent_pid_str), "%d", getppid());
                strcpy(&buffer[j], parent_pid_str);
                j += strlen(parent_pid_str);
                i += 3; // Skip the $$$
            }
            // Handle numeric variables like $13536
            else if (isdigit(arg[i + 1]))
            {
                i++; // Skip the $

                // Collect digits after $
                char num_str[128];
                int num_len = 0;

                // Extract all digits
                while (isdigit(arg[i]))
                {
                    num_str[num_len++] = arg[i++];
                }
                num_str[num_len] = '\0';

                // Remove the first digit and copy the rest
                if (num_len > 1)
                {
                    strcpy(&buffer[j], &num_str[1]); // Skip the first digit
                    j += (num_len - 1); // Move buffer index forward by num_len - 1
                }
                else
                {
                    // If only one digit, just copy it as is
                    strcpy(&buffer[j], num_str);
                    j += num_len;
                }
            }
            else
            {
                // Handle other variable expansions (environment variables)
                char var_name[128];
                int var_len = 0;
                i++;  // Skip the $

                // Extract variable name
                while (arg[i] != '\0' && (isalnum(arg[i]) || arg[i] == '_'))
                {
                    var_name[var_len++] = arg[i++];
                }
                var_name[var_len] = '\0';

                // Get the value of the environment variable
                char *env_value = getenv(var_name);
                if (env_value)
                {
                    strcpy(&buffer[j], env_value);
                    j += strlen(env_value);
                }
            }
        }
        else
        {
            buffer[j++] = arg[i++];
        }
    }
    buffer[j] = '\0';  // Null-terminate the final string
}

void echo(const char *message, bool no_newline)
{
    printf("%s", message);
    if (!no_newline)
        printf("\n");
}

int builtin_echo(t_data *data, char **args)
{
    (void)data;  // Not used currently, but present for future use if needed

    if (args[0] && strcmp(args[0], "echo") == 0)
    {
        bool no_newline = false;
        int i = 1;  // Start from the second argument (because args[0] is "echo" itself)

        // Check for the presence of the -n flag
        while (args[i] && is_n_flag(args[i]))
        {
            no_newline = true;
            i++;
        }

        char message[1024] = "";  // Array to store the final message
        bool first_word = true;

        // Build the message by concatenating the remaining arguments
        while (args[i])
        {
            if (!first_word)
                strcat(message, " ");

            char expanded[1024] = "";  // Array to store expanded variables
            expand_variables(args[i], expanded);
            
            strcat(message, expanded);
            first_word = false;
            i++;
        }

        // Print the final message
        echo(message, no_newline);
    }
    else
    {
        // If no valid "echo" command, print a new line
        write(1, "\n", 1);
    }

    return 0;
}