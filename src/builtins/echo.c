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

void echo(const char *message, bool no_newline)
{
    printf("%s", message);
    if (!no_newline)
        printf("\n");
}

int builtin_echo(t_data *data, char **args)
{
    (void)data;  // Unused for now, but you can use it if needed later

    if (args[0] && strcmp(args[0], "echo") == 0)
    {
        bool no_newline = false;
        int i = 1;  // Start from 1 to skip the "echo" command itself

        // Check for -n flags
        while (args[i] && is_n_flag(args[i]))
        {
            no_newline = true;
            i++;
        }

        char message[1024] = "";  // Buffer for the final message
        bool first_word = true;

        // Build the message by concatenating arguments
        while (args[i])
        {
            if (!first_word)
                strcat(message, " ");
            strcat(message, args[i]);
            first_word = false;
            i++;
        }

        // Print the final message
        echo(message, no_newline);
    }
    else
    {
        // If no valid command is found, print a newline
        write(1, "\n", 1);
    }

    return 0;
}