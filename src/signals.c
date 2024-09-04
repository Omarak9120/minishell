void handle_signal(int signum) {
    if (signum == SIGINT) {
        printf("\nminishell> ");
        fflush(stdout);
    }
}
