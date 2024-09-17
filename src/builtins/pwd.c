#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int         builtin_pwd(t_data *data, char **args)
{
    (void)data;
    (void)args;
    return (0);
//     char *cwd = malloc(9999);
//     if (cwd == NULL)
//     {
//         perror("minishell");
//         return;
//     }
//     if (getcwd(cwd, 9999) != NULL)
//         printf("%s\n", cwd);
//     else
//         perror("minishell");
//     free(cwd);
}

// int main(int argc, char *argv[])
// {
//     ft_pwd();
//     return 0;
// }