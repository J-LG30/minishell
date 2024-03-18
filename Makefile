# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 23:44:24 by jle-goff          #+#    #+#              #
#    Updated: 2024/03/16 23:44:25 by jle-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = @cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -static-libsan -g
LIB = -lreadline

SRCS = main.c exec_command.c lexer/lexer.c lexer/lexer_lst_utils.c \
		parser/parser.c parser/ast_helper.c parser/command.c parser/command_production.c \
		parser/redirections.c parser/print_ast.c parser/free_ast.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(@) $(LIB)

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re