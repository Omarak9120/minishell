#include "../../includes/minishell.h" 


int main(void)
{
    // Modifiable string for tokenization
    char input[] = "echo \"hello world\" >> file";
    // char input[] = "echo \"hello \\\"world\\\"\"";
    // char input[] = "echo \"hello world\" > output.txt";
    // char input[] = " | grep txt || sort echo omar";
    // char input[] = "echo \"file contents\" > output.txt";
    // char input[] = " cat << output ???";
    // char input[] = "echo Hello\\ World";
    // char input[] = "echo \"Hello World";
    // char input[] = "echo \"Unmatched quote";
    
    t_token *token_list = tokenize_input(input);
    
    if (!token_list) {
        // Handle error
        printf("Error tokenizing input.\n");
        return 1;
    }
    
    // Validate the token list before printing tokens
    if (validate_tokens(token_list) == SUCCESS) {
        printf("Token list is valid.\n");
    } else {
        printf("Token list has syntax errors.\n");
    }
    
    // Now we can traverse and print the token list for testing
    t_token *current = token_list;
    while (current != NULL)
    {
        printf("Token: %s, Type: %d\n", current->str, current->type);
        current = current->next;
    }
    
    // Free the token list after use
    free_token_list(token_list);
    return 0;
}
