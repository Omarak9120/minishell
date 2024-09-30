#include "../../includes/minishell.h"

char *logical_path = NULL; 
char *prev_dir = NULL;

void update_logical_path(const char *new_path)
{
    if (logical_path != NULL)
        free(logical_path);
    logical_path = strdup(new_path);
    if (logical_path == NULL)
        perror("minishell: strdup");
}

void print_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else if (logical_path != NULL)
        printf("%s\n", logical_path);
    else
        fprintf(stderr, "minishell: pwd: error retrieving current directory\n");
}

int builtin_cd(t_data *data, char **args)
{
    char *home;
    char cwd[1024];
    char *temp_dir = NULL;
    int cwd_valid = 1;

    (void)data;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        cwd_valid = 0; 
        fprintf(stderr, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
    }

    if (cwd_valid)
    {
        temp_dir = strdup(cwd);
        if (temp_dir == NULL)
        {
            perror("minishell: strdup");
            return 1;
        }
    }

    if (args[1] == NULL || strcmp(args[1], "~") == 0)
    {
        home = getenv("HOME");
        if (home == NULL)
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            free(temp_dir);
            return 1;
        }
        if (chdir(home) != 0)
        {
            perror("minishell");
            free(temp_dir);
            return 1;
        }
        update_logical_path(home);
    }
    else if (strcmp(args[1], "-") == 0)
    {
        if (prev_dir == NULL)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            free(temp_dir);
            return 1;
        }
        if (chdir(prev_dir) != 0)
        {
            perror("minishell");
            free(temp_dir);
            return 1;
        }
        printf("%s\n", prev_dir);
        update_logical_path(prev_dir);
    }
    else
    {
        if (strcmp(args[1], "..") == 0)
        {
            if (!cwd_valid)
            {
                char *last_slash = strrchr(logical_path, '/');
                if (last_slash != NULL)
                {
                    *last_slash = '\0';  
                    if (chdir(logical_path) != 0)
                    {
                        free(temp_dir);
                        return 1;
                    }
                    update_logical_path(logical_path);
                }
            }
            else
            {
                if (chdir("..") != 0)
                {
                    free(temp_dir);
                    return 1;
                }
                char *last_slash = strrchr(logical_path, '/');
                if (last_slash != NULL)
                    *last_slash = '\0';
                update_logical_path(logical_path);
            }
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("minishell");
                free(temp_dir);
                return 1;
            }
            if (cwd_valid)
                update_logical_path(args[1]);
        }
    }

    if (prev_dir != NULL)
        free(prev_dir);
    prev_dir = temp_dir;

    if (getcwd(cwd, sizeof(cwd)) != NULL)

        update_logical_path(cwd);

    return 0;
}
