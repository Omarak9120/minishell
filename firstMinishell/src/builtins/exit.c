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
    if (args[1] == NULL) 
    {
        exit_status = data->exit_status;
        printf("exit\n");
        exit(exit_status);
    }
    if (!is_numeric(args[1])) 
    {
        printf("minishell: exit: %s: numeric argument required\n", args[1]);
        exit(2);
    }
    exit_status = ft_atoi(args[1]);
    if (args[2] != NULL) 
    {
        fprintf(stderr, "minishell: exit: too many arguments\n");
        exit(1);
    }
    printf("exit\n");
    exit(exit_status);
}
