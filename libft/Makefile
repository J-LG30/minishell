# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 19:50:18 by jle-goff          #+#    #+#              #
#    Updated: 2023/04/24 19:49:44 by jle-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = @cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_itoa.c ft_memccpy.c ft_split.c ft_strnstr.c \
       ft_bzero.c ft_memchr.c ft_strchr.c ft_strrchr.c ft_calloc.c \
       ft_memcmp.c ft_strdup.c ft_strtrim.c ft_isalnum.c ft_memcpy.c \
       ft_striteri.c ft_substr.c ft_isalpha.c ft_memmove.c \
       ft_strjoin.c ft_tolower.c ft_isascii.c ft_memset.c ft_strlcat.c \
       ft_toupper.c ft_isdigit.c ft_putchar_fd.c ft_strlcpy.c \
       ft_islower.c ft_putendl_fd.c ft_strlen.c ft_isprint.c \
       ft_putnbr_fd.c ft_strmapi.c ft_isupper.c \
       ft_putstr_fd.c ft_strncmp.c ft_strndup.c


BSRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar -crs $(NAME) $(OBJS)

bonus: $(OBJS) $(BOBJS)
	@ar -crs $(NAME) $(OBJS) $(BOBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re