/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:41:35 by eosfryd           #+#    #+#             */
/*   Updated: 2021/09/02 19:42:13 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_of_rules(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (1);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]) == 0 && ft_isdigit(var[i]) == 0
			&& var[i] != '_')
			return (1);
	}
	return (0);
}

int	check_name(char *var, char **vari, char **able)
{
	int		rez;
	char	*tmp;
	int		i;

	i = 0;
	rez = 0;
	if (!check_var(var))
		return (-1);
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

void	add_env_plus_equal(char *vari, char *able, t_shell *glob, int j)
{
	t_alist	*list;
	int		flag;
	int		i;

	i = 0;
	flag = -1;
	list = list_init();
	while (glob->our_envp && glob->our_envp[i])
	{
		if (ft_strncmp(vari, glob->our_envp[i], ft_strlen(vari)) == 0)
		{
			if (j == 1)
				add_new_arg(ft_strjoin(glob->our_envp[i], able), ' ', 0, list);
			else
				add_new_arg(ft_strjoin(vari, able), ' ', 0, list);
			flag = i++;
		}
		else
			add_new_arg(ft_strdup(glob->our_envp[i++]), ' ', 0, list);
	}
	if (flag == -1)
		add_new_arg(ft_strjoin(vari, able), ' ', 0, list);
	ft_clean(glob->our_envp);
	glob->our_envp = var_adder_series_S(list->ahead, list);
	free_a_list(list);
}

void	ft_export2(char *var, char	*vari, char	*able)
{
	printf("minishell: export: '%s': not a valid identifier\n", var);
	free(vari);
	free(able);
	g_var.stat_code = 1;
}

void	ft_export(char **var_arr, t_shell *glob)
{
	char	*vari;
	char	*able;
	int		flag;
	int		i;

	i = 0;
	vari = NULL;
	able = NULL;
	while (var_arr && var_arr[i] && *(var_arr[i]))
	{
		flag = check_name(var_arr[i], &vari, &able);
		if (flag == -1)
			return (ft_export2(var_arr[i], vari, able));
		else
			add_env_plus_equal(vari, able, glob, flag);
		free(vari);
		free(able);
		i++;
	}
}
