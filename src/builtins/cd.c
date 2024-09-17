#include "../../includes/minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

int         builtin_cd(t_data *data, char **args)  // Built-in 'cd' command
{
    (void)data;
    if (args[1] == NULL)
    {
        char *home = getenv("HOME");
        if (home == NULL)
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return 1;
        }
        if (chdir(home) != 0)
        {
            perror("minishell");
            return 1;
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("minishell");
            return 1;
        }
    }
    return 0;
}
