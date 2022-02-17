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

char	*add_var_add(char *str, char *var)
{
	int	i;

	i = 0;
	str++;
	if (!ft_strncmp(str, ft_strnstr(var, "=",
				ft_strlen(var) + 1), ft_strlen(str) + 1))
	{
		str = (char *) ft_calloc(ft_strlen(var), sizeof(char));
		while (var[i] && var[i] != '+')
		{
			str[i] = var[i];
			i++;
		}
		while (var[i + 1])
		{
			str[i] = var[i + 1];
			i++;
		}
		return (str);
	}
	return (0);
}

int	ill_come_up_with_a_name_later(char *var, char **vari, char **able)
{
	int		rez;
	char	*tmp;
	int		i;

	i = 0;
	rez = 0;
	while (var[i] != '=' && !(var[i] == '+' && var[i + 1] == '='))
		i++;
	if (var[i] == '=')
		*vari = ft_substr(var, 0, i + 1);
	if (var[i] == '+')
	{
		tmp = ft_substr(var, 0, i);
		*vari = ft_strjoin(tmp, "=");
		free(tmp);
		rez = 1;
	}
	tmp = var;
	tmp += (i + 1);
	if (rez == 1)
		tmp++;
	*able = ft_strdup(tmp);
	return (rez);
}

void	add_var_plus_equal(char *vari, char *able, t_shell *glob, int j)
{
	t_alist	*list;
	int		flag;
	int		i;

	i = 0;
	flag = -1;
	list = list_init();
	while (glob->var_mass && glob->var_mass[i])
	{
		if (ft_strncmp(vari, glob->var_mass[i], ft_strlen(vari)) == 0)
		{
			if (j == 1)
				add_new_arg(ft_strjoin(glob->var_mass[i], able), ' ', 0, list);
			else
				add_new_arg(ft_strjoin(vari, able), ' ', 0, list);
			flag = i++;
		}
		else
			add_new_arg(ft_strdup(glob->var_mass[i++]), ' ', 0, list);
	}
	if (flag == -1)
		add_new_arg(ft_strjoin(vari, able), ' ', 0, list);
	ft_clean(glob->var_mass);
	glob->var_mass = var_adder_series_S(list->ahead, list);
	free_a_list(list);
}

void	add_var(char *var, t_shell *glob, int i)
{
	char	*vari;
	char	*able;

	i = ill_come_up_with_a_name_later(var, &vari, &able);
	add_var_plus_equal(vari, able, glob, i);
	free(vari);
	free(able);
}

char	*var_cut_plus(char *var, int i)
{
	char	*str;

	str = ft_strnstr(var, "+=", ft_strlen(var) + 1);
	if (str)
	{
		str++;
		if (! ft_strncmp(str, ft_strnstr(var, "=",
					ft_strlen(var) + 1), ft_strlen(str) + 1))
		{
			str = (char *) ft_calloc(ft_strlen(var), sizeof(char));
			while (var[i] && var[i] != '+')
			{
				str[i] = var[i];
				i++;
			}
			while (var[i + 1])
			{
				str[i] = var[i + 1];
				i++;
			}
			return (str);
		}
	}
	return (0);
}
