#include "../../includes/minishell.h"

int builtin_pwd(t_data *data, char **args)
{
    (void)args;
    (void)data;

    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 0;
    }
    else
    {
        perror("pwd");
        return 1;
    }
}