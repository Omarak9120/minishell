#include "../../includes/minishell.h"

int builtin_cd(t_data *data, char **args)
{
    static char *prev_dir = NULL;
    char *home;
    char cwd[1024];

    (void)data;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    if (args[1] == NULL || strcmp(args[1], "~") == 0)
    {
        home = getenv("HOME");
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
    else if (strcmp(args[1], "-") == 0)
    {
        if (prev_dir == NULL)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            return 1;
        }
        if (chdir(prev_dir) != 0)
        {
            perror("minishell");
            return 1;
        }
        printf("%s\n", prev_dir);
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("minishell");
            return 1;
        }
    }

    free(prev_dir);
    prev_dir = ft_strdup(cwd);

    return 0;
}