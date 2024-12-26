#include "../../includes/minishell.h"

extern char *logical_path;

int builtin_pwd(t_data *data, char **args) {
    (void)args;
    (void)data;

    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        if (logical_path != NULL)
            free(logical_path);
        logical_path = strdup(cwd);
    } else {
        if (logical_path != NULL) {
            printf("%s/..\n", logical_path);
        } else {
            fprintf(stderr, "minishell: pwd: error retrieving current directory\n");
        }
    }

    return 0;
}


