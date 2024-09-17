#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_numeric(const char *str) 
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i]) 
    {
        if (!isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

int         builtin_exit(t_data *data, char **args)
{
    (void)data;
    (void)args;
    return (0);
//     int exit_status = 0;
//     if (args[1] == NULL) 
//     {
//         printf("exit\n");
//         exit(exit_status);
//     }
//     if (!is_numeric(args[1])) 
//     {
//         printf("minishell: exit: %s: numeric argument required\n", args[1]);
//         exit(255);
//     }
//     exit_status = atoi(args[1]);
//     if (args[2] != NULL) 
//     {
//         fprintf(stderr, "minishell: exit: too many arguments\n");
//         return;
//     }
//     printf("exit\n");
//     exit(exit_status);
}
