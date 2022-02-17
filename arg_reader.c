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

void	argreader_s_def_vars(int *jtem, int *z)
{
	*jtem = 0;
	*z = 0;
}

/* Формирует слово по пробелу в качестве делиметра, 
так же учитывает порядок и количество ковычек */
int	argreader_s(int item, char quot, char *line, t_shell *glob)
{
	int	jtem;
	int	z;

	argreader_s_def_vars(&jtem, &z);
	if ((line[item] == '<' && line[item + 1] == '<')
		|| (line[item] == '>' && line[item + 1] == '>'))
		jtem += 2;
	else if (line[item] == '<' || line[item] == '>')
		jtem = 1;
	while (line[item + jtem] != '\0' && line[item + jtem] != '<'
		&& line[item + jtem] != '>' && line[item + jtem] != '|'
		&& line[item + jtem] != quot && (line[item + jtem] != 34)
		&& (line[item + jtem] != 39))
		jtem++;
	if ((line[item + jtem] == 34) || (line[item + jtem] == 39))
		z = 1;
	add_new_arg(ft_substr(line, item, jtem), quot, z, glob->arg_list);
	if (line[item + jtem] == 34 || line[item + jtem] == 39
		|| line[item + jtem] != '<' || line[item + jtem] != '>')
	{
		item = item + jtem - 1;
		return (item);
	}
	item += jtem;
	return (item);
}

/* Формирует слово по ковычкам в качестве делиметра, 
так же учитывает порядок и количество ковычек */
int	argreader_q(int item, char quot, char *line, t_shell *glob)
{
	int	jtem;
	int	z;

	z = 0;
	jtem = 0;
	item++;
	while (line[item + jtem] != '\0' && line[item + jtem] \
	!= '|' && line[item + jtem] != quot)
		jtem++;
	if (line[item + jtem] != quot)
		puts("quote error\n");
	if ((line[item + jtem] == quot && line[item + jtem + 1] == 34) \
	|| (line[item + jtem] == quot && line[item + jtem + 1] == 39) \
	|| (line[item + jtem] == quot && ft_is(line[item + jtem + 1])))
		z = 1;
	add_new_arg(ft_substr(line, item, jtem), quot, z, glob->arg_list);
	item += jtem;
	return (item);
}

/* Дублирует переменные окружения для дальнейшей работы */
char	**init_envp(char **envp)
{
	int		i;
	int		j;
	char	**env_dup;

	i = 0;
	while (envp[i])
		i++;
	env_dup = malloc(sizeof(char *) * (i + 1));
	env_dup[i] = NULL;
	j = 0;
	while (j != i)
	{
		env_dup[j] = ft_strdup(envp[j]);
		j++;
	}
	return (env_dup);
}
