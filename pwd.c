#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void ft_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("minishell");
    }
}
