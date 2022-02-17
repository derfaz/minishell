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

void	change_var2(t_shell *glob, char	*tmp, int index)
{
	free((glob->var_mass)[index]);
	(glob->var_mass)[index] = tmp;
}

void	change_var_add(char *tmp, t_shell *glob, char *full_name, int index)
{
	char	*val;

	val = ft_strchr(tmp, '=');
	val ++;
	if (index > -1)
	{
		(glob->var_mass)[index] = \
		ft_strjoin_free((glob->var_mass)[index], val, 1, 0);
		free(tmp);
		return ;
	}
	index = is_env_var(full_name, glob);
	if (index > -1)
	{
		(glob->our_envp)[index] = \
		ft_strjoin_free((glob->our_envp)[index], val, 1, 0);
		free(tmp);
		return ;
	}
	free(tmp);
}

void	change_var(char *full_name, t_shell *glob)
{
	int		index;
	char	*tmp;

	if (!full_name)
		return ;
	index = is_var(full_name, glob);
	tmp = var_cut_plus(full_name, 0);
	if (!tmp)
	{
		tmp = ft_strdup(full_name);
		if (index > -1)
			return (change_var2(glob, tmp, index));
		index = is_env_var(full_name, glob);
		if (index > -1)
		{
			free((glob->our_envp)[index]);
			(glob->our_envp)[index] = tmp;
			return ;
		}
	}
	else
		change_var_add(tmp, glob, full_name, index);
}
