CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft
LIBFT = libft/libft.a
SRC = src/minishell.c \
      src/lexer/lexer_main.c \
      src/lexer/lexer_utils.c \
      src/lexer/lexer.c \
      src/lexer/test_lexer.c \
      src/lexer/token.c \
      src/lexer/token_types.c \
      src/lexer/token_utils.c \
      src/lexer/token_validation.c \
      # Add other files from `src/parser`, `src/redirection`, etc. as needed

OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
