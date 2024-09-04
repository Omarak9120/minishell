#include "minishell.h"

void execute(char **args) {
    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        if (execve(args[0], args, NULL) == -1) {
            perror("minishell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {  // Fork failed
        perror("minishell");
    } else {  // Parent process
        waitpid(pid, NULL, 0);
    }
}
