
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

bool check_quotes(const char *str)
{
    int i;
    bool inside_quote = false;

    i = 0;
    while (i < strlen(str))
    {
        if (str[i] == '"')
            inside_quote = !inside_quote;
        i++;
    }
    return !inside_quote;
}

void echo(const char *message)
{
    if (check_quotes(message))
        printf("%s\n", message);
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        char message[1024] = "";
        int i = 2;
        while (i < argc)
        {
            if (i > 2)
            {
                strcat(message, " ");
            }
            strcat(message, argv[i]);
            i++;
        }
        echo(message);
    }
    else
        write(1, "\n", 1);
    return 0;
}