#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd (s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd (s, fd);
	ft_putchar_fd ('\n', fd);
}
// Handler for SIGINT (Ctrl + C)
void handle_sigint(int sig) {
    (void)sig;
    // Move to a new line, clear the current input, and redisplay the prompt
    ft_putendl_fd("", 0);
    rl_replace_line("", 0);  // Clear the line buffer
    rl_on_new_line();        // Handle the new line
    rl_redisplay();          // Redisplay the prompt
}

int main() {
    char *input;

    // Set signal handlers
    signal(SIGINT, handle_sigint);   // Ctrl + C
    signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl + \

    while (1) {
        // Display the prompt and read user input
        input = readline("minishell> ");  // Correctly set the prompt here
        
        // Handle EOF (Ctrl + D)
        if (!input) {
            write(1, "exit\n", 5);
            break;
        }

        if (input[0] != '\0') {
            // Add non-empty input to history
            add_history(input);
        }

        // Your command processing logic here

        free(input);  // Free the input buffer allocated by readline
    }

    return 0;
}
