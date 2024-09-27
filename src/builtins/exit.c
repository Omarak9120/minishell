#include "../../includes/minishell.h"

bool is_numeric(const char *str) 
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')  // Handle optional sign
        i++;
    while (str[i]) 
    {
        if (!ft_isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

int builtin_exit(t_data *data, char **args)
{
    int exit_status;

    // If no argument is provided, use the last exit status (from data)
    if (args[1] == NULL) 
    {
        exit_status = data->exit_status;  // Default to the last command's exit status
        printf("exit\n");
        exit(exit_status);
    }

    // If the first argument is not numeric, print an error and exit with 255
    if (!is_numeric(args[1])) 
    {
        printf("minishell: exit: %s: numeric argument required\n", args[1]);
        exit(2);
    }

    // Convert the first argument to an integer (valid numeric argument)
    exit_status = ft_atoi(args[1]);

    // If there are more than one argument, print an error and return 1
    if (args[2] != NULL) 
    {
        fprintf(stderr, "minishell: exit: too many arguments\n");
        exit(1);
    }

    // Normal exit with the provided numeric exit status
    printf("exit\n");
    exit(exit_status);
}
