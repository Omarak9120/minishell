#include "../../includes/minishell.h"

bool is_numeric(const char *str) 
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')  // Allow optional + or - sign
        i++;
    while (str[i]) 
    {
        if (!isdigit(str[i]))  // Check if character is not a digit
            return false;
        i++;
    }
    return true;
}

int builtin_exit(t_data *data, char **args)
{
    int exit_status = 0;

    (void)data;  // Currently unused, but could be useful for other exit-related operations

    // If no arguments, simply exit with status 0
    if (args[1] == NULL) 
    {
        printf("exit\n");
        exit(exit_status);
    }

    // Check if the first argument is numeric
    if (!is_numeric(args[1])) 
    {
        printf("minishell: exit: %s: numeric argument required\n", args[1]);
        exit(255);  // Non-numeric argument should exit with status 255
    }

    // Convert the numeric argument to an integer
    exit_status = atoi(args[1]);

    // If there are too many arguments
    if (args[2] != NULL) 
    {
        fprintf(stderr, "minishell: exit: too many arguments\n");
        return 1;  // Return error code 1, but do not exit the shell
    }

    // If all checks pass, exit with the provided status
    printf("exit\n");
    exit(exit_status);
}
