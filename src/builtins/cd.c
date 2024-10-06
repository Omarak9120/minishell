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

int builtin_cd(t_data *data, char **args) {
    char *home;
    char cwd[PATH_MAX];
    char *temp_dir = NULL;
    int cwd_valid = 1;

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        cwd_valid = 0;
        fprintf(stderr, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
    }

    // Save the current directory before changing
    if (cwd_valid) {
        temp_dir = strdup(cwd);  // Store current directory into temp_dir
        if (temp_dir == NULL) {
            perror("minishell: strdup");
            data->exit_status = 1;
            return 1;
        }
    }

    // Handle cd command arguments
    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            free(temp_dir);
            data->exit_status = 1;
            return 1;
        }
        if (chdir(home) != 0) {
            perror("minishell");
            free(temp_dir);
            data->exit_status = 1;
            return 1;
        }
        update_logical_path(home);
    } else if (strcmp(args[1], "-") == 0) {
        if (prev_dir == NULL) {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            free(temp_dir);
            data->exit_status = 1;
            return 1;
        }
        if (chdir(prev_dir) != 0) {
            perror("minishell");
            free(temp_dir);
            data->exit_status = 1;
            return 1;
        }
        printf("%s\n", prev_dir);
        update_logical_path(prev_dir);
    } else if (strcmp(args[1], "..") == 0) {
        if (chdir("..") != 0) {
            perror("minishell");
            free(temp_dir);
            data->exit_status = 1;
            return 1;
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("minishell");
            free(temp_dir);
            data->exit_status = 1;
            return 1;
        }
    }

    // Update prev_dir with the last valid directory (before changing to the new one)
    if (prev_dir != NULL)
        free(prev_dir);
    prev_dir = temp_dir;

    // Update OLDPWD environment variable
    char olpwd[PATH_MAX];
    snprintf(olpwd, sizeof(olpwd), "OLDPWD=%.*s", (int)(sizeof(olpwd) - 8), prev_dir);  // Ensure it doesn't overflow
    add_env_variable(data, olpwd);

    // Update PWD to reflect the new current directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char new_pwd[PATH_MAX];
        snprintf(new_pwd, sizeof(new_pwd), "PWD=%.*s", (int)(sizeof(new_pwd) - 5), cwd);  // Ensure it doesn't overflow
        add_env_variable(data, new_pwd);
    }

    return 0;
}

