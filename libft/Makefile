# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 17:38:44 by eosfryd           #+#    #+#              #
#    Updated: 2021/09/01 17:50:59 by eosfryd          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC		= ft_atoi.c ft_atoi_ll.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_strcpy.c\
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c\
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
		ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
		ft_strncmp.c ft_strcmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c\
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_split.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_get_next_line.c\
		ft_itoa_ll.c ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstnew.c ft_lstsize.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_realloc.c\
		ft_isnumber.c ft_lstallfree.c ft_isint.c ft_strjoin_free.c ft_memdel.c ft_clean_str_by_adress.c

SRCOBJ	= $(patsubst %.c,%.o,$(SRC))

HEADERS	= libft.h

FLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

MLB		= ar rc

CC		= gcc

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(MLB) $(NAME) $(SRCOBJ)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(SRCOBJ)
 
fclean: clean
	rm -rf $(NAME)

re: fclean all clean


.PHONY: all clean fclean
