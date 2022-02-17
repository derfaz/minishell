NAME = minishell

NAME_LIBFT = libft.a

SRCS = main.c parce.c parce1.c parce2.c envp_arg_handler.c ft_echo.c \
	ft_unset.c var1.c var2.c var3.c var4.c ft_export.c str_arr_funs.c command_funs1.c \
	redirections.c ft_cd.c ft_execve.c ft_pwd.c ft_exit.c check_atoi_input.c sig_handlers.c \
	command_funs2.c command_funs3.c def_path_val.c var_adder.c list_funs.c arg_reader.c
OBJS = ${SRCS:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror

RM = rm -f

LIBFT_DIR = libft/

$(NAME):	${OBJS}
			make -C $(LIBFT_DIR)
			gcc ${CFLAGS} -o ${NAME} $(LIBFT_DIR)libft.a ${OBJS} -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/

all:	${NAME}

clean:
		${RM} ${OBJS}
		make clean -C $(LIBFT_DIR)

fclean:	clean
		${RM} ${NAME}
		make fclean -C $(LIBFT_DIR)

re:	fclean all clean
	${RM} ${OBJS}
	make clean -C $(LIBFT_DIR)

.PHONY:	re all clean fclean