/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:38:16 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:38:16 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_params(t_shell *glob, char **env)
{
	g_var.erstr = 0;
	g_var.code = ft_strdup("0");
	g_var.pidie = INT_MIN;
	g_var.stat_code = 0;
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlslash);
	signal(SIGUSR1, sigusr1_handler);
	glob->our_envp = NULL;
	glob->arg_mass = NULL;
	glob->arg_list = NULL;
	glob->redir = NULL;
	glob->comma_list = NULL;
	glob->var_mass = (char **)malloc(sizeof(char *));
	glob->var_mass[0] = NULL;
	glob->std_out = dup(1);
	glob->std_in = dup(0);
	glob->our_envp = init_envp(env);
	change_SHLVL(glob);
	add_var("?=0", glob, 0);
}

void	write_stat_code(t_shell *glob)
{
	char	*full_name;
	char	*str;

	full_name = ft_strdup("?=");
	str = ft_itoa(g_var.stat_code);
	full_name = ft_strjoin_free(full_name, str, 1, 1);
	change_var(full_name, glob);
	free(full_name);
}

void	main_no_line(void)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "exit\n", ft_strlen("exit\n"));
	exit(0);
}

/*
void	make_SOS()
{
	puts("\a");
	sleep(1);
	puts(".");
	puts("\a");
	sleep(1);
	puts(".");
	puts("\a");
	sleep(1);
	puts(".");
	puts("\a");
	sleep(2);
	puts("_");
	puts("\a");
	sleep(2);
	puts("_");
	puts("\a");
	sleep(2);
	puts("_");
	puts("\a");
	sleep(1);
	puts(".");
	puts("\a");
	sleep(1);
	puts(".");
	puts("\a");
	sleep(1);
	puts(".");
	puts("\a");
}
*/
void	main2(int ac, char **av, char **env, t_shell *glob)
{
	if (av || env)
		ac = ac + 1;
	init_params(glob, env);
}

int	main(int ac, char **av, char **env)
{
	int				out;
	char			*line;
	t_comma_list	*list;
	t_shell			glob;

	main2(ac, av, env, &glob);
	out = 1;
	while (out)
	{
		if (!isatty(0))
			out = 0;
		line = readline("minishell$ ");
		if (!line)
			main_no_line();
		add_history(line);
		list = parce(line, &glob);
		free(line);
		wrapper_comma_init(list, &glob);
		write_stat_code(&glob);
		if (list)
			free_t_comma_list(list);
		if (g_var.erstr)
			free(g_var.erstr);
	}
}
