# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davda-si <davda-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 21:24:04 by davda-si          #+#    #+#              #
#    Updated: 2024/04/26 16:47:38 by davda-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = @cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address #-static-libsan
LIB = -lreadline

#ASAN_OPTIONS=symbolize=1
#ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer)

SRCS = 	main.c free.c lexer/lexer.c lexer/lexer_lst_utils.c lexer/quotes.c parser/connect_tree.c \
		parser/parser.c parser/ast_helper.c parser/command.c parser/command_production.c \
		parser/redirections.c parser/print_ast.c exec/child.c exec/exe.c \
		b_ins/env.c b_ins/env_utils.c b_ins/export.c b_ins/echo.c b_ins/pwd.c b_ins/cd.c\
		b_ins/exit.c b_ins/unset.c exec/utils_exec.c signals/signals.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

#version for my mac
#LIB_DIR = -L /usr/local/opt/readline/lib

all: $(NAME)

#version for my mac

#$(NAME): $(OBJS) $(LIBFT_A)
#	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(@) $(LIB) $(LIB_DIR) -I /usr/local/opt/readline/include

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

#valgrind --suppressions=readline.supp --track-fds=all --leak-check=full --show-leak-kinds=all --track-origins=yes  ./minishell