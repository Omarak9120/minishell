# minishell
The objective of this project is to create a simple shell, taking bash as a reference.

This shell has the following features:

+ Display a **prompt** when waiting for a new command.

+ Have a working **history**.

+ Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path).

+ Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data strucutures.

+ Not interpret unclosed quotes or special characters which are not required by the subject as \ (backslash) or ; (semicolon).

+ Handle ' (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.

+ Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).

+ Implement **redirections**:

	* '<' should redirect input.
	* '>' should redirect output.
	* '<<' should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn't have to update the history!
	* '>>' should redict output in append mode.

+ Implement **pipes** (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

+ Handle **environment variables** (**$** followed by a sequence of characters) which should expand their values.

+ Handle **$?** which should expand to the exit status of the most recently executed foreground pipeline.

+ Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in **bash**.

+ In interactive mode:

	* ctrl-C displays a new prompt on a new line.
	* ctrl-D exits the shell.
	* ctrl-\ does nothing.

+ Your shell must implement the following **builtins**:
	* echo with option -n
	* cd with only a relative or absolute path
	* pwd with no options
	* export with no options
	* unset with no options
	* env with no options
	* exit with no options

As a bonus, it has to implement:

+ && and || with parenthesis for priorities.

+ Wildcards * should work for the current working directory.


References:

1. 42 Network. (2023). Minishell - As beautiful as a shell, Version 7.1 [PDF file]. https://projects.intra.42.fr/projects/42cursus-minishell. (Accessed March 4, 2024)

2. Free Software Foundation. (2022). GNU Bash manual. https://www.gnu.org/savannah-checkouts/gnu/bash/manual/. (Accessed March 4, 2024)

3. The Open Group. (2018). The Open Group Base Specifications Issue 7, 2018 edition. https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/. (Accessed March 4, 2024)

