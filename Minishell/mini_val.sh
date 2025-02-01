#!/bin/bash

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp -q --trace-children=yes \
	--trace-children-skip=/usr/*,./*,*/bin/*  ./minishell