# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 11:03:46 by josfelip          #+#    #+#              #
#    Updated: 2024/06/19 12:02:24 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
DEBUG_NAME = minishell_debug
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3

# Paths for libraries
LIB_PATH = ./lib
LIB_NAME = libft.a

# Colors Definition 
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths definitions
HEADER_PATH = ./include/
HEADER_FILE = builtins.h dictionary.h libftplus.h mini_get_cmd_path.h minishell.h trashman_env.h trashman.h
HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))
OBJ_PATH = ./obj/
DEBUG_OBJ_PATH = ./obj_debug/
SOURCES_PATH = ./src/
SOURCES = 00_utils.c 02_ctrl_signal.c 02_utils.c 03_utils.c 05_tokenizer.c 05_utils_1.c 05_utils_2.c 05_utils_3.c 05_utils_4.c 05_utils_5.c 05_utils_6.c 05_utils_7.c 06_parser.c 06_utils.c 07_expansion.c 07_utils_1.c 07_utils_2.c 07_utils_3.c 07_utils_4.c 08_redirect.c 08_utils_1.c 08_utils_2.c 09_execute.c 10_get_cmd_path.c 11_open_pipes.c 12_mini_execve.c 12_utils_1.c 12_utils_2.c 12_utils_3.c 12_utils_4.c 13_remake_environ.c 14_split_expansion.c 15_heredoc.c 15_utils_1.c 93_builtin_exit.c 94_builtin_env.c 95_builtin_cd.c 96_builtin_pwd.c 97_builtin_unset.c 97_utils_1.c 98_builtin_export.c 98_utils_1.c 99_builtin_echo.c ft_dictionary.c ft_dictionary_utils.c ft_substr_mem.c ft_trashman.c ft_trashman_env.c
MANDATORY_SOURCES = $(addprefix $(SOURCES_PATH), $(SOURCES))

ifdef WITH_DEBUG
  NAME = $(DEBUG_NAME)
  CFLAGS = $(DFLAGS)
  OBJ_PATH = ./obj_debug/
endif

OBJECTS = $(addprefix $(OBJ_PATH), $(SOURCES:%.c=%.o))

all: libft $(OBJ_PATH) $(NAME)

libft:
	@make --directory=$(LIB_PATH) --no-print-directory

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJECTS) $(OBJ_PATH)main.o
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(OBJ_PATH)main.o -L $(LIB_PATH) -lft -lreadline
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| MINISHELL executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@echo " "

$(OBJ_PATH)%.o: $(SOURCES_PATH)%.c $(HEADER)
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(HEADER_PATH)
	@echo " "

$(OBJ_PATH)main.o: main.c $(HEADER)
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(HEADER_PATH)
	@echo " "

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	-rm -rf $(OBJ_PATH)
	-rm -rf $(DEBUG_OBJ_PATH)

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@rm -rf $(NAME)
	@rm -rf $(DEBUG_NAME)
	@make fclean -C $(LIB_PATH) --no-print-directory

re: fclean
	@make --no-print-directory

rec: clean
	@make --no-print-directory

.PHONY: all clean fclean re libft debug rec
