
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

bool is_n_flag(const char *arg)
{
    if (arg[0] == '-')
    {
        for (int i = 1; arg[i] != '\0'; i++)
        {
            if (arg[i] != 'n')
                return false;
        }
        return true;
    }
    return false;
}

void echo(const char *message, bool no_newline)
{
    printf("%s", message);
    if (!no_newline)
        printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "echo") == 0)
    {
        bool no_newline = false;
        int i = 2;
        while (i < argc && is_n_flag(argv[i]))
        {
            no_newline = true;
            i++;
        }
        char message[1024] = "";
        bool first_word = true;
        while (i < argc)
        {
            if (!first_word)
                strcat(message, " ");
            strcat(message, argv[i]);
            first_word = false;
            i++;
        }
        echo(message, no_newline);
    }
    else
        write(1, "\n", 1);

    return 0;
}