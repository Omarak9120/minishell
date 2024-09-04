# Project name
NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# Directories
MKDIR = mkdir
RM = rm -rf
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/

# Subdirectories in src/
SRC_SUBDIRS = builtins execution lexer parser redirection signals utils

# Source files in main src directory and subdirectories
SRC_FILES = minishell.c
BUILTINS_FILES = $(wildcard $(SRC_DIR)builtins/*.c)
EXEC_FILES = $(wildcard $(SRC_DIR)execution/*.c)
LEXER_FILES = $(wildcard $(SRC_DIR)lexer/*.c)
PARSER_FILES = $(wildcard $(SRC_DIR)parser/*.c)
REDIR_FILES = $(wildcard $(SRC_DIR)redirection/*.c)
SIGNAL_FILES = $(wildcard $(SRC_DIR)signals/*.c)
UTILS_FILES = $(wildcard $(SRC_DIR)utils/*.c)

# Combine all source files
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES)) \
       $(BUILTINS_FILES) \
       $(EXEC_FILES) \
       $(LEXER_FILES) \
       $(PARSER_FILES) \
       $(REDIR_FILES) \
       $(SIGNAL_FILES) \
       $(UTILS_FILES)

# Create object files, preserving directory structure in obj/
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Header files
HEADERS = $(INC_DIR)minishell.h

# Build target
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

# Rule to create object files from source files and make sure directories exist
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)  # Create necessary directories for obj/
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ_DIR)

# Full clean, including executable
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
