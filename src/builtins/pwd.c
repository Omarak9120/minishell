#include "../../includes/minishell.h"

extern char *logical_path;

int builtin_pwd(t_data *data, char **args)
{
    (void)args;
    (void)data;

    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        if (logical_path != NULL)
        {
            printf("%s\n", logical_path);
        }
        else
        {
            perror("pwd");
            return 1;
        }
    }

    return 0;
}
