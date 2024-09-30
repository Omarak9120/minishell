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
    else if (strcmp(args[1], "..") == 0)  // Handle ".." logic
    {
        if (chdir("..") != 0)
        {
            perror("minishell");
            free(temp_dir);
            return 1;
        }
        update_logical_path("..");  // Update logical path to ".."
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

    if (prev_dir != NULL)
        free(prev_dir);
    prev_dir = temp_dir;

    // Update OLDPWD environment variable
    size_t cwd_length = strlen(cwd);
    size_t olpwd_length = cwd_length + 10; // 10 for "OLDPWD=" + null terminator
    char olpwd[olpwd_length]; // Allocate a buffer with sufficient size

    if ((size_t)snprintf(olpwd, sizeof(olpwd), "OLDPWD=%s", cwd) >= sizeof(olpwd)) {
        fprintf(stderr, "Warning: OLPWD string may be truncated\n");
    }
    add_env_variable(data, olpwd);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_logical_path(cwd);

    return 0;
}
