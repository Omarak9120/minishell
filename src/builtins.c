int cd_command(char **args) {
    if (chdir(args[1]) != 0) {
        perror("minishell");
    }
}
