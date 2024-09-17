#include "../../includes/minishell.h"

int builtin_pwd(t_data *data, char **args)
{
    (void)args;  // args is unused in the pwd command
    (void)data;  // data is unused, but might be needed for other functionality

    char cwd[PATH_MAX];  // Buffer to store the current working directory
    
    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);  // Print the current working directory
        return 0;  // Success
    } else {
        perror("pwd");  // If an error occurs, print the error message
        return 1;  // Return error code
    }
}