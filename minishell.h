/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 19:13:34 by eosfryd           #+#    #+#             */
/*   Updated: 2021/09/09 13:42:59 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# include <term.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_arg
{
	struct s_arg	*next;
	char			*args;
	char			qoute;
	int				space;
	int				ipipe;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_alist
{
	t_arg		*ahead;
	int			lenght;
}				t_alist;

typedef struct s_comma_token
{
	struct s_comma_token	*next;
	int						fd_in;
	char					**arguments;
	char					**direction;
	int						fd_out;
	int						ipipe;
	struct s_comma_token	*prew;
}							t_comma_token;

typedef struct s_comma_list
{
	t_comma_token			*head;
	int						len;
}							t_comma_list;

typedef struct s_shell
{
	t_alist			*arg_list;
	t_comma_list	*comma_list;
	char			**our_envp;
	char			**arg_mass;
	char			**var_mass;
	char			**redir;
	int				std_in;
	int				std_out;
}				t_shell;

typedef struct s_er_exit
{
	char			*erstr;
	char			*code;
	int				pidie;
	int				stat_code;
}				t_er_exit;

t_er_exit	g_var;

/* не классифицируется */
void			make_direction(int i, t_comma_token *comma,
					t_shell *glob, char **massdir);
void			wrapper_comma_init(t_comma_list *comma, t_shell *glob);
void			free_t_comma_list(t_comma_list *comma);
void			free_a_list(t_alist *list);
char			*replace_var(char *str, int j, int f, char **envp);

/* вспомогательные функции */

/* инициализация переменных */
char			**init_envp(char **envp);

/* парсер */
t_comma_list	*parce(char *str, t_shell *glob);
char			*arg_parce(char *line, t_shell *glob);
char			**post_parce(t_arg	*tmp, int len);
void			argreader_s_def_vars(int *jtem, int *z);
int				argreader_s(int item, char quot, char *line, t_shell *glob);
int				argreader_q(int item, char quot, char *line, t_shell *glob);
size_t			ft_strlen_mod(const char *str);
int				arg_checker(t_alist *list);
void			mid_parce(t_shell *glob);
char			**redir_handler(t_arg *arg, int flag, t_shell *glob);
void			add_new_comma_arg(t_comma_list *l, char **c, char **d, int p);

/*variables*/
char			**var_adder_series_S(t_arg *tmp, t_alist *lol);
void			add_var(char *var, t_shell *glob, int i);
void			change_var(char *full_name, t_shell *glob);
void			change_var2(t_shell *glob, char	*tmp, int index);
int				is_var(char *name, t_shell *glob);
int				is_env_var(char *name1, t_shell *glob);
char			*is_var_full(char *name, t_shell *glob);
char			*var_val(char *name, t_shell *glob);
char			*def_var_name(char *full_name);
void			del_var(char *full_name, int flag, t_shell *glob);
void			del_var_index(char **arr, int index);
int				check_var(char *full_name);
int				is_num(char *str);
void			change_SHLVL(t_shell *glob);
void			var_adder_3000(char *shlvl, t_shell *glob);
char			**var_adder_series_S(t_arg *tmp, t_alist *lol);
char			*var_cut_plus(char *var, int i);
int				ft_is(int c);

/* команды */
t_alist			*list_init(void);
void			add_new_arg(char *content, char quots, int z,
					t_alist *arg_list);
void			def_command(char **arg_arr, t_shell *glob);
char			*ft_echo(char **args);
void			ft_export(char **var_arr, t_shell *glob);
void			display_str_arr(char **a);
void			ft_unset(char **args, t_shell *glob);
void			ft_execve(char **arg_arr, t_shell *glob, char *tmp, char *name);
char			*def_path_val(t_shell *glob);
void			ft_exit(char **arg_arr);
char			*ft_pwd(void);
void			ft_cd(char **arg_arr, t_shell *glob);
void			country_roads_take_me_home(t_shell *glob);
char			*is_cmd_ok(char **cmd, char **paths);
int				is_our_command(char *cmd);
void			exec_our_command(char **arg_arr, t_shell *glob);
char			*cut_path(char *buf);
char			*find_arg(char *str, int s, int l, char **envp);
int				check_atoi_input2(char *arg, char *max, int sign);
int				check_atoi_input(char *arg, char *max);
t_comma_token	*first_proc(t_shell *glob, t_comma_token *tmp, int *pipefd);
t_comma_token	*mid_proc(t_shell *glob,
					t_comma_token *tmp, int **pipefd, int p);
t_comma_token	*ft_commad(t_shell *glob, t_comma_token *tmp);
t_comma_token	*last_proc(t_shell *glob, t_comma_token *tmp, int *pipefd);

/* str_arr_funs */
void			printy_pie(char **a);
int				str_arr_len(char **arr);
char			*triple_join(char *one, char *two, char *three);
char			**cpy_str_arr(char **arg_arr);

/* signals */
void			ctrlc(int sig);
void			ctrlslash(int sig);
void			sigusr1_handler(int sig);

/* списки */
t_arg			*create_item(char *content, char quots, int z);
void			add_new_arg(char *content, char quots, int z,
					t_alist *arg_list);
t_alist			*list_init(void);
void			free_a_list(t_alist *list);

#endif