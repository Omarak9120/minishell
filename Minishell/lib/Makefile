NAME = libft.a

GET_NEXT_LINE = sources/get_next_line/get_next_line.a
GET_NEXT_LINE_PATH = sources/get_next_line/


FUNCTIONS = sources/functions/functions.a
FUNCTIONS_PATH = sources/functions/

all: $(FUNCTIONS) $(GET_NEXT_LINE) $(NAME)

$(GET_NEXT_LINE):
	make -C $(GET_NEXT_LINE_PATH)

$(FUNCTIONS):
	make -C $(FUNCTIONS_PATH)

$(NAME):
	ar -rcT $(NAME) $(FUNCTIONS) $(GET_NEXT_LINE)

clean:
	make clean -C $(FUNCTIONS_PATH)
	make clean -C $(GET_NEXT_LINE_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(FUNCTIONS_PATH)
	make fclean -C $(GET_NEXT_LINE_PATH)

re: fclean all

.PHONY: all clean fclean re bonus
