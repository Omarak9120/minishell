CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft
LIBFT = libft/libft.a

SRC = src/minishell.c \
	  $(wildcard src/builtins/*.c) \
	  $(wildcard src/utils/*.c) \
	  src/heder.c \
      $(wildcard src/lexer/*.c) \
      $(wildcard src/parser/*.c) \
	  $(wildcard src/execution/*.c) \
      $(wildcard src/signals/*.c)

# Change to store object files in obj/ while keeping their directory structure
OBJ = $(SRC:src/%.c=obj/%.o)
NAME = minishell

# Create build directory structure
OBJDIRS = $(sort $(dir $(OBJ)))

all: $(NAME)

# Link the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "\033[31m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \033[0m"
	@echo "\033[31m████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \033[0m"
	@echo "\033[31m██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \033[0m"
	@echo "\033[31m██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \033[0m"
	@echo "\033[31m██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\033[0m"
	@echo "\033[31m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\033[0m"
	@echo "\033[0m" 

# Pattern rule to compile .o files from .c files in subdirectories
obj/%.o: src/%.c | $(OBJDIRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for minishell.c in the root of src/
obj/minishell.o: src/minishell.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure object directories are created
$(OBJDIRS):
	mkdir -p $(OBJDIRS)

# Clean only object files and intermediate directories (not the executable)
clean:
	rm -f $(OBJ)
	rm -rf obj/

# Full clean, including the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all