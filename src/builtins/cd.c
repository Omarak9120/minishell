#include "../../includes/minishell.h"

int builtin_cd(t_data *data, char **args)
{
    static char *prev_dir = NULL;
    char *home;
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        ft_perror("getcwd");
        return 1;
    }

    if (args[1] == NULL || my_strcmp(args[1], "~") == 0)
    {
        home = my_getenv(data->env, "HOME");
        if (home == NULL)
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return 1;
        }
        if (chdir(home) != 0)
        {
            ft_perror("minishell");
            return 1;
        }
    }
    else if (my_strcmp(args[1], "-") == 0)
    {
        if (prev_dir == NULL)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            return 1;
        }
        if (chdir(prev_dir) != 0)
        {
            ft_perror("minishell");
            return 1;
        }
        printf("%s\n", prev_dir);
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            ft_perror("minishell");
            return 1;
        }
    }

    free(prev_dir);
    prev_dir = ft_strdup(cwd);

    return 0;
}