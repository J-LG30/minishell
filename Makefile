# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 21:24:04 by davda-si          #+#    #+#              #
#    Updated: 2024/05/02 16:14:34 by jle-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = @cc
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address #-static-libsan
LIB = -lreadline

#ASAN_OPTIONS=symbolize=1
#ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer)

SRCS = 	main.c free.c free2.c lexer/lexer.c lexer/lexer_lst_utils.c lexer/quotes.c\
		lexer/expansion.c parser/connect_tree.c parser/parser.c parser/ast_helper.c\
		parser/command.c parser/command_production.c print_branch.c\
		parser/redirections.c parser/print_ast.c exec/child.c exec/exe.c\
		b_ins/env.c b_ins/env_utils.c b_ins/export.c b_ins/echo.c b_ins/pwd.c b_ins/cd.c\
		b_ins/exit.c b_ins/unset.c exec/utils_exec.c exec/utils_exec2.c signals/signals.c\
		exec/utils_exec3.c exec/utils_exec4.c exec/cmds.c b_ins/export_utils.c \
		exec/heredoc_expansion.c b_ins/export_sort.c exec/utils_exec5.c\
		signals/sig_heredoc.c lexer/expansion_utils.c parser/connect_tree_utils.c\
		lexer/quotes_utils.c\

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

#version for my mac
#LIB_DIR = -L /usr/local/opt/readline/lib

all: $(NAME)

#version for my mac

#$(NAME): $(OBJS) $(LIBFT_A)
#	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o  $(@) $(LIB) -lreadline $(LIB_DIR)
#-I /usr/local/opt/readline/include

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(@) $(LIB)

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

#valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes  ./minishell