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

char	*cut_path(char *buf)
{
	int		i;
	int		num;
	char	**path_arr;

	num = 0;
	path_arr = ft_split(buf, '/');
	ft_memdel((void **)&buf);
	num = str_arr_len(path_arr);
	if (num == 1)
		return (ft_strdup("/"));
	i = 0;
	buf = 0;
	while (i < num - 1)
	{
		buf = ft_strjoin_free(buf, "/", 1, 0);
		buf = ft_strjoin_free(buf, path_arr[i], 1, 0);
		i++;
	}
	ft_clean(path_arr);
	return (buf);
}

static void	def_cd_path(char **path_arr, char **buf)
{
	while (*path_arr)
	{
		if (!ft_strncmp(*path_arr, "..", 3) && ft_strncmp(*buf, "/", 2))
			*buf = cut_path(*buf);
		else if (ft_strncmp(*path_arr, ".", 2))
		{
			if ((*buf)[ft_strlen(*buf) - 1] != '/')
				*buf = ft_strjoin_free(*buf, "/", 1, 0);
			*buf = ft_strjoin_free(*buf, *path_arr, 1, 0);
		}
		else
		{
			printf("*path_arr = %s\n", *path_arr);
			*buf = ft_strjoin_free(*buf, "/", 1, 0);
			*buf = ft_strjoin_free(*buf, *path_arr, 1, 0);
		}
		path_arr++;
	}
}

void	ft_cd2(char *buf, char **arg_arr)
{
	if (chdir(buf))
	{
		free(buf);
		buf = triple_join(ft_strdup("cd: "), ft_strdup(*arg_arr), \
		ft_strdup(": no such file or directory\n"));
		g_var.erstr = buf;
		g_var.stat_code = 1;
	}
}

void	country_roads_take_me_home(t_shell *glob)
{
	char	*home;

	home = find_arg("HOME=", 0, 5, glob->our_envp);
	if (!home)
	{
		puts("West Virginia, mountain mama\ntake me $HOME, country roads");
		g_var.stat_code = 1;
	}
	else if (chdir(home))
	{
		home = triple_join(ft_strdup("cd: "), home, \
		ft_strdup(": no such file or directory\n"));
		g_var.erstr = ft_strdup(home);
		g_var.stat_code = 1;
	}
	free(home);
	g_var.pidie = 0;
}

void	ft_cd(char **arg_arr, t_shell *glob)
{
	char	*buf;
	char	**path_arr;

	if (!*arg_arr)
	{
		country_roads_take_me_home(glob);
		return ;
	}
	if ((!ft_strncmp(arg_arr[0], ".", 2) || !ft_strncmp(arg_arr[0], "./", 3)))
		return ;
	path_arr = ft_split(arg_arr[0], '/');
	if (**arg_arr != '/')
	{
		buf = (char *) ft_calloc(PATH_MAX, sizeof(char));
		buf = getcwd(buf, PATH_MAX);
	}
	else
		buf = ft_strdup("/");
	def_cd_path(path_arr, &buf);
	ft_cd2(buf, arg_arr);
}
