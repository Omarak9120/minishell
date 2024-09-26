#include "../../includes/minishell.h"

int g_signal_exit_status = 0;  // Global variable to track signal exit status

void ft_sigint_handler_beforecmd(int sig) {
    (void)sig;  // Ignore the actual signal argument
    rl_replace_line("", 0);  // Clear the current line
    ft_putchar_fd('\n', 1);  // Print newline to reset the prompt
    rl_on_new_line();
    rl_redisplay();
}

// Signal handler during command execution (Ctrl+C)
void ft_sigint_handler_incmd(int sig)
{
    g_signal_exit_status = sig;
    write(1, "\n", 1);  // Print newline
}

// Setup signal handling for shell input (readline prompt)
void ft_signal_setup_for_input(void)
{
    signal(SIGINT, ft_sigint_handler_beforecmd);  // Handle Ctrl+C at the prompt
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl+\??
}


// Reset signal handling for child process (during command execution)
void ft_reset_signals(void)
{
    signal(SIGINT, SIG_DFL);  // Default Ctrl+C behavior (terminate the child process)
    signal(SIGQUIT, SIG_DFL); // Default Ctrl+\ behavior
}

// Check and handle any caught signals after command execution
void ft_check_signal(t_data *data)
{
    if (g_signal_exit_status == SIGINT) {
        data->exit_status = 130;  // Set exit status to 130 for Ctrl+C
        g_signal_exit_status = 0;  // Reset signal status
    } else if (g_signal_exit_status == SIGQUIT) {
        data->exit_status = 131;  // Set exit status to 131 for Ctrl+\??
        g_signal_exit_status = 0;  // Reset signal status
    }
}

