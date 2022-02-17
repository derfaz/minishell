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

int	check_var(char *full_name)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!full_name || !*full_name || !ft_strchr(full_name, '='))
		return (0);
	while (full_name[len] && full_name[len] != '=')
		len++;
	if (!full_name[len + 1])
		return (0);
	while (i < len)
	{
		if (i == 0 && !(ft_isalpha(full_name[i]) || full_name[i] == '_'))
			return (0);
		if (!(ft_isalnum(full_name[i]) || full_name[i] == '_'
				|| full_name[i] == '+'))
			return (0);
		if (full_name[i] == '+' && (!full_name[i + 1]
				|| full_name[i + 1] != '='))
			return (0);
		i++;
	}
	return (1);
}

void	del_var(char *full_name, int flag, t_shell *glob)
// flag = 0 -- var, flag = 1 -- env_var, flag = 2 -- both
{
	int	index;

	if (flag == 0)
	{
		index = is_var(full_name, glob);
		del_var_index(glob->var_mass, index);
	}
	else if (flag == 1)
	{
		index = is_env_var(full_name, glob);
		del_var_index(glob->our_envp, index);
	}
	else
	{
		index = is_var(full_name, glob);
		del_var_index(glob->var_mass, index);
		index = is_env_var(full_name, glob);
		del_var_index(glob->our_envp, index);
	}
}

void	del_var_index(char **arr, int index)
{
	int	len;
	int	i;

	len = str_arr_len(arr);
	if (!arr || index == -1 || index >= len)
		return ;
	i = 0;
	while (i < index)
		i++;
	while (i < len - 1)
	{
		ft_memdel((void **)&arr[i]);
		arr[i] = ft_strdup(arr[i + 1]);
		i++;
	}
	arr[len - 1] = 0;
}

char	*def_var_name(char *full_name)
{
	char	*short_name;
	int		len;
	int		i;

	len = 0;
	while (full_name[len] && full_name[len] != '=')
		len++;
	if (full_name[len - 1] == '+')
		len--;
	short_name = (char *) ft_calloc(len + 1, sizeof (char));
	i = 0;
	while (i < len)
	{
		short_name[i] = full_name[i];
		i++;
	}
	short_name[len] = 0;
	return (short_name);
}

char	*var_val(char *name, t_shell *glob)
{
	char	*ret;
	char	**tmp_var;

	tmp_var = glob->var_mass;
	while (tmp_var && *(tmp_var))
	{
		if (ft_strnstr(*(tmp_var), name, ft_strlen(name) + 1))
		{
			ret = ft_strchr(*(tmp_var), '=');
			return (ret + 1);
		}
		(tmp_var)++;
	}
	tmp_var = glob->our_envp;
	while (tmp_var && *(tmp_var))
	{
		if (ft_strnstr(*(tmp_var), name, ft_strlen(name) + 1))
		{
			ret = ft_strchr(*(tmp_var), '=');
			return (ret + 1);
		}
		(tmp_var)++;
	}
	return (0);
}
