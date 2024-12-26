#include "../../includes/minishell.h"

int g_signal_exit_status = 0;

// Signal handler for shell prompt (Ctrl+C)
void ft_sigint_handler_beforecmd(int sig) {
    (void)sig;
    g_signal_exit_status = SIGINT;  // Mark that SIGINT was received
    rl_replace_line("", 0);  // Clear the current line
    ft_putchar_fd('\n', 1);  // Print newline to reset the prompt
    rl_on_new_line();
    rl_redisplay();
}

// Signal handler during command execution (Ctrl+C)
void ft_sigint_handler_incmd(int sig) {
    g_signal_exit_status = sig;
    write(1, "\n", 1);
}

// Signal setup for shell input (readline prompt)
void ft_signal_setup_for_input(void) {
    signal(SIGINT, ft_sigint_handler_beforecmd);  // Ctrl+C in shell prompt
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl+\ in prompt
}

// Signal setup for command execution
void ft_signal_setup_for_execution(void) {
    signal(SIGINT, ft_sigint_handler_incmd);  // Ctrl+C during command execution
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl+\ during command execution
}

// Reset signals to default (for child processes)
void ft_reset_signals(void) {
    signal(SIGINT, SIG_DFL);  // Default Ctrl+C behavior in child processes
    signal(SIGQUIT, SIG_DFL); // Default Ctrl+\ behavior in child processes
}

// Check and handle caught signals after command execution
void ft_check_signal(t_data *data) {
    if (g_signal_exit_status == SIGINT) {
        data->exit_status = 130;  // Exit code for Ctrl+C
        g_signal_exit_status = 0;  // Reset the global signal status
    } else if (g_signal_exit_status == SIGQUIT) {
        data->exit_status = 131;  // Exit code for Ctrl+"\""
        g_signal_exit_status = 0;  // Reset the global signal status
    }
}
