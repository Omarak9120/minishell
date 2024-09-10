#include "minishell.h"

// Define token types
int get_token_type(char *str) {
    if (ft_strcmp(str, "|") == 0)
        return PIPE;
    else if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0)
        return REDIRECT;
    else
        return WORD;
}
