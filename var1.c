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

int	is_var_add(char *name, t_shell *glob)
{
	char	*tmp;
	int		var_index;
	int		i;

	var_index = 0;
	while (glob->var_mass && glob->var_mass[var_index])
	{
		tmp = ft_strnstr(glob->var_mass[var_index], name,
				ft_strlen(glob->var_mass[var_index]));
		i = 0;
		if (tmp)
		{
			while (name[i] && (name[i] != '='))
			{
				if (name[i] != tmp[i])
					break ;
				i++;
			}
			if (!(name[i]) && tmp[i] == '=')
				return (var_index);
		}
		var_index++;
	}
	return (-1);
}

int	is_var(char *name1, t_shell *glob)
{
	char	*name;
	int		ret;

	if (!name1)
		return (0);
	name = def_var_name(name1);
	ret = is_var_add(name, glob);
	free(name);
	return (ret);
}

int	is_env_var_add(char *name, t_shell *glob)
{
	char	*tmp;
	int		var_index;
	int		i;

	var_index = 0;
	while (glob->our_envp && glob->our_envp[var_index])
	{
		tmp = ft_strnstr(glob->our_envp[var_index], name,
				ft_strlen(glob->our_envp[var_index]));
		i = 0;
		if (tmp)
		{
			while (name[i] && (name[i] != '='))
			{
				if (name[i] != tmp[i])
					break ;
				i++;
			}
			if (!(name[i]) && tmp[i] == '=')
				return (var_index);
		}
		var_index++;
	}
	return (-1);
}

int	is_env_var(char *name1, t_shell *glob)
{
	char	*name;
	int		ret;

	if (!name1)
		return (0);
	name = def_var_name(name1);
	ret = is_env_var_add(name, glob);
	free(name);
	return (ret);
}

char	*is_var_full(char *name, t_shell *glob)
{
	char	*tmp;
	int		i;

	if (!name)
		return (0);
	i = 0;
	while (glob->var_mass && glob->var_mass[i])
	{
		tmp = ft_strnstr(glob->var_mass[i], name, ft_strlen(name) + 1);
		if (tmp)
		{
			while (*name)
			{
				if (*name != *tmp)
					break ;
				name++;
				tmp++;
			}
			if (!(*name) && (*tmp) == '=')
				return (glob->var_mass[i]);
		}
		i++;
	}
	return (0);
}
