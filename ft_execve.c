/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 16:54:41 by eosfryd           #+#    #+#             */
/*   Updated: 2021/08/30 17:50:12 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve_full_path(char **arg_arr, t_shell *glob)
{
	pid_t	chpid;

	chpid = fork();
	if (chpid == 0)
	{
		if (execve(*arg_arr, arg_arr + 1, glob->our_envp))
			g_var.erstr = ft_strdup("minishell: command not found\n");
	}
	else
		waitpid(chpid, &g_var.stat_code, 0);
}

void	ft_execve_child(char *fname, char	**paths,
						char **arg_arr, t_shell *glob)
{
	int		ex_rez;
	char	*tmp;
	int		i;

	ex_rez = 1;
	i = 0;
	while (paths[i] && ex_rez)
	{
		tmp = ft_strjoin("/", *arg_arr);
		fname = ft_strjoin(paths[i], tmp);
		free(tmp);
		ex_rez = execve(fname, arg_arr, glob->our_envp);
		if (fname)
			free(fname);
		i++;
	}
	if (!(paths[i]))
	{
		printf("minishell: %s: command not found\n", *arg_arr);
		exit(127);
	}
}

void	otdelnaya_function(char *content, t_shell *glob)
{
	char	*subie;

	subie = ft_strchr(content, '=');
	if (subie && *subie && *(subie + 1))
	{
		if (!check_var(content))
		{
			printf("minishell: %s: command not found\n", content);
			g_var.stat_code = 127;
		}
		else
		{
			if (is_var(content, glob) == -1 && is_env_var(content, glob) == -1)
				add_var(content, glob, 0);
			else if (!(is_env_var(content, glob) == -1))
				ft_export(&content, glob);
			else
				change_var(content, glob);
		}
	}
}

void	ft_execve2(char **arg_arr, t_shell *glob, char *tmp, char *fname)
{
	char	**paths;
	char	**tmp2;
	pid_t	chpid;

	if (ft_strchr(*arg_arr, '/'))
		return (ft_execve_full_path(arg_arr, glob));
	tmp = def_path_val(glob);
	paths = ft_split(tmp, ':');
	tmp2 = paths;
	if (tmp)
		free(tmp);
	chpid = fork();
	if (chpid == 0)
		ft_execve_child(fname, paths, arg_arr, glob);
	else
		waitpid(chpid, &g_var.stat_code, 0);
	if (tmp2 && *tmp2)
		ft_clean(tmp2);
}

void	ft_execve(char **arg_arr, t_shell *glob, char *tmp, char *fname)
{
	while (arg_arr && *arg_arr && ft_strchr(*arg_arr, '='))
	{
		otdelnaya_function(*arg_arr, glob);
		if (g_var.stat_code == 127)
			return ;
		arg_arr++;
	}
	if (!(arg_arr && *arg_arr))
		return ;
	ft_execve2(arg_arr, glob, tmp, fname);
}
