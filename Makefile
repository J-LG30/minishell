# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 21:24:04 by davda-si          #+#    #+#              #
#    Updated: 2024/04/23 16:22:38 by jle-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = @cc
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -static-libsan
LIB = -lreadline

#version for my mac
LIB_DIR = -L /usr/local/opt/readline/lib

SRCS = 	main.c lexer/lexer.c lexer/lexer_lst_utils.c lexer/quotes.c \
		parser/parser.c parser/ast_helper.c parser/connect_tree.c \
		parser/command.c parser/command_production.c \
		parser/redirections.c parser/print_ast.c parser/free_ast.c exec/child.c exec/exe.c \
		b_ins/env.c b_ins/env_utils.c b_ins/export.c \
		exec/utils_exec.c signals/signals.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

#version for my mac
$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(@) $(LIB) $(LIB_DIR) -I /usr/local/opt/readline/include

# $(NAME): $(OBJS) $(LIBFT_A)
# 	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(@) $(LIB)

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