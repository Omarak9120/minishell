// #include "minishell.h"

// // Define token types
// // Define token types
// int get_token_type(char *str) {
//     if (ft_strcmp(str, "|") == 0)
//         return PIPE;
//     else if (ft_strcmp(str, ">") == 0)
//         return REDIRECT_OUT;  // Output redirection
//     else if (ft_strcmp(str, "<") == 0)
//         return REDIRECT_IN;   // Input redirection
//     else if (ft_strcmp(str, ">>") == 0)
//         return APPEND;        // Append redirection
//     else if (ft_strcmp(str, "<<") == 0)
//         return HEREDOC;       // Heredoc redirection
//     else if (ft_strcmp(str, "&") == 0)
//         return BACKGROUND;    // Background process
//     else if (ft_strcmp(str, ";") == 0)
//         return SEMICOLON;     // Command separator
//     else if (ft_strcmp(str, "&&") == 0)
//         return AND;           // Logical AND
//     else if (ft_strcmp(str, "||") == 0)
//         return OR;            // Logical OR
//     else
//         return WORD;          // Default type for commands/words
// }
