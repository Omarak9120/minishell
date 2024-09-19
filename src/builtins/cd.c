#include "../../includes/minishell.h"

int builtin_cd(t_data *data, char **args) // Built-in 'cd' command
{
    static char *prev_dir = NULL; // To store the previous directory
    char *home;
    char cwd[1024];

    (void)data; // Unused parameter for now

    if (getcwd(cwd, sizeof(cwd)) == NULL) // Get current directory
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
        printf("%s\n", prev_dir); // Print the previous directory
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("minishell");
            return 1;
        }
    }

    // Update the previous directory
    free(prev_dir);
    prev_dir = strdup(cwd); // Save the current directory as previous

    return 0;
}