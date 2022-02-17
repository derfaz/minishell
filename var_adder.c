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

char	**var_adder_series_S(t_arg *tmp, t_alist *lol)
{
	char	**rez;
	int		item;

	if (!(lol->lenght))
		return (NULL);
	item = 0;
	rez = malloc(sizeof(char *) * (lol->lenght + 1));
	rez[lol->lenght] = NULL;
	while (item != lol->lenght)
	{
		rez[item] = ft_strdup(tmp->args);
		tmp = tmp->next;
		item++;
	}
	return (rez);
}

//функция смотрит в envp и меняет shlvl на одноименный аргумент из функции
//если в envp нет shlvl то функция добавляет его
void	var_adder_3000(char *shlvl, t_shell *glob)
{
	t_alist	*list;
	int		index;
	int		i;

	i = 0;
	index = -1;
	list = list_init();
	while (glob->our_envp[i])
	{
		if (ft_strncmp("SHLVL=", glob->our_envp[i], 6) == 0)
		{
			add_new_arg(ft_strdup(shlvl), ' ', 0, list);
			index = i++;
		}
		else
			add_new_arg(ft_strdup(glob->our_envp[i++]), ' ', 0, list);
	}
	if (index == -1)
		add_new_arg(ft_strdup(shlvl), ' ', 0, list);
	ft_clean(glob->our_envp);
	glob->our_envp = var_adder_series_S(list->ahead, list);
	free_a_list(list);
}

void	change_SHLVL(t_shell *glob)
{
	char	*shlvl;
	char	*eee;
	char	*aaa;
	int		i;

	shlvl = NULL;
	if (glob && glob->our_envp)
		shlvl = find_arg("SHLVL=", 0, 6, glob->our_envp);
	if (!shlvl || (is_num(shlvl) == 0))
		var_adder_3000("SHLVL=1", glob);
	else if (ft_atoi((const char *)shlvl) < 0)
		var_adder_3000("SHLVL=0", glob);
	else
	{
		i = ft_atoi((const char *)shlvl);
		eee = ft_itoa(i + 1);
		aaa = ft_strjoin("SHLVL=", eee);
		var_adder_3000(aaa, glob);
		free(aaa);
		free(eee);
	}
	if (shlvl)
		free(shlvl);
}
