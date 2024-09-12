#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

void ft_pwd(void)
{
    char *cwd = malloc(PATH_MAX);
    if (cwd == NULL)
    {
        perror("minishell");
        return;
    }
    if (getcwd(cwd, PATH_MAX) != NULL)
        printf("%s\n", cwd);
    else
        perror("minishell");
    free(cwd);
}

int main(int argc, char *argv[])
{
    ft_pwd();
    return 0;
}