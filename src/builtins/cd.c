#include "../../includes/minishell.h"

char *logical_path = NULL; 
char *prev_dir = NULL;

int update_logical_path(const char *new_path)
{
    if (logical_path != NULL)
        free(logical_path);

    logical_path = strdup(new_path);

    if (logical_path == NULL)
    {
        perror("minishell: strdup");
        return 1;
    }

    return 0;
}

int builtin_cd(t_data *data, char **args)
{
    char *home;
    char cwd[1024];

    (void)data;

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
        if (strcmp(args[1], "..") == 0)
        {
            if (logical_path != NULL)
            {
                char *new_logical_path = malloc(strlen(logical_path) + 4);
                if (new_logical_path == NULL)
                {
                    perror("minishell: malloc");
                    return 1;
                }
                strcpy(new_logical_path, logical_path);
                strcat(new_logical_path, "/..");
                free(logical_path);
                logical_path = new_logical_path;
            }
        }
        if (chdir(args[1]) != 0)
        {
            perror("minishell");
            return 1;
        }
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_logical_path(cwd);
    else
        fprintf(stderr, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");

    return 0;
}