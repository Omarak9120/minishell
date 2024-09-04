NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = src/minishell.c src/execute.c src/parsing.c src/builtins.c src/redirection.c src/signals.c src/utils.c
OBJS = $(SRC:.c=.o)
INC = -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
