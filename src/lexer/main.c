// #include "../../includes/minishell.h" 

// // int main(void)
// // {
// //     // Modifiable string for tokenization
// //     char input[] = "echo \"hello world\" >> file";
// //     // char input[] = "echo \"hello \\\"world\\\"\"";
// //     // char input[] = "echo \"hello world\" > output.txt";
// //     // char input[] = " | grep txt || sort echo omar";
// //     // char input[] = "echo \"file contents\" > output.txt";
// //     // char input[] = " cat << output ???";
// //     // char input[] = "echo Hello\\ World";
// //     // char input[] = "echo \"Hello World";
// //     // char input[] = "echo \"Unmatched quote";

// #include "../../includes/minishell.h"

// void run_test(char *input) {
//     printf("Input: %s\n", input);

//     t_token *token_list = tokenize_input(input);

//     if (!token_list) {
//         // Handle error
//         printf("Error tokenizing input.\n\n");
//         return;
//     }

//     // Validate the token list before printing tokens
//     if (validate_tokens(token_list) == SUCCESS) {
//         printf("Token list is valid.\n");
//     } else {
//         printf("Token list has syntax errors.\n");
//     }

//     // Now we can traverse and print the token list for testing
//     t_token *current = token_list;
//     while (current != NULL) {
//         printf("Token: %s, Type: %d\n", current->str, current->type);
//         current = current->next;
//     }

//     printf("\n");

//     // Free the token list after use
//     free_token_list(token_list);
// }

// int main(void) {
//     char *test_cases[] = {
//         "echo omar ''",
//         "echo 'Hello \'World\''",
//         "echo 'Hello World' \"Test\"",
//         "echo \"He said 'hello'\"",
//         "echo 'He said \"hello\"'",
//         "echo 'He said \"hello\"'",
//         "echo 'Hello World",
//         "echo \"Hello World",
//         "echo 'Hello \\\"escaped\\\" World' \"Test \\\"123\\\"\"",
//         "echo '' \"\"",
//         "cat 'file with spaces.txt' > 'output file.txt'",
//         "echo \"Hello \\\"World\\\"\"",
//         "echo 'Hello \\'World\\''",
//         "echo 'test1' | grep 'test2'",
//         "'echo hello' 'grep world'",
//         "'echo \"hello\" world'",
//         "echo 'Hello & Goodbye' && echo \"Hello (World)\"",
//         "echo 'backslash \\ in quotes' \"double \\backslash\""
//     };

//     int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

//     for (int i = 0; i < num_tests; i++) {
//         run_test(test_cases[i]);
//     }

//     return 0;
// }
