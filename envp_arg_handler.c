/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_arg_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:38:59 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:38:59 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Ищет и выдает содержимое переменной окружения */
char	*find_arg(char *str, int s, int l, char **envp)
{
	char	*rez;
	char	*arg;
	int		i;
	int		j;

	i = 0;
	arg = ft_substr(str, s, l - s);
	while (envp[i] && !ft_strnstr(envp[i], arg, ft_strlen(arg)))
		i++;
	if (!envp[i])
	{
		free(arg);
		return (NULL);
	}
	j = 0;
	while (envp[i][j] != '=')
		j++;
	rez = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - (j + 1));
	free(arg);
	return (rez);
}

/* Служебная функция. Соединяет три слова воедино,
 в случае если слов меньше, соединит и их,
 отчищает память задействованных в объединении строк,
для объединения использовать ТОЛЬКО строки,
 для которых была аллоцирована память*/
char	*triple_join(char *one, char *two, char *three)
{
	char	*rez;
	char	*tmp;

	if (!one)
		rez = (ft_strjoin(two, three));
	else if (!two)
		rez = (ft_strjoin(one, three));
	else if (!three)
		rez = (ft_strjoin(one, two));
	else
	{
		rez = ft_strjoin(one, two);
		tmp = rez;
		rez = ft_strjoin(tmp, three);
		free(tmp);
	}
	free(one);
	free(two);
	free(three);
	return (rez);
}

/* Производит замену $ARG на перемнную или перемнную окружения */
char	*replace_var(char *str, int j, int f, char **envp)
{
	char	*before;
	char	*after;
	char	*prametr;
	char	*rez;
	int		i;

	i = j;
	before = ft_substr(str, 0, j - 1);
	while (str[j] && str[j] != ' ' && str[j] != 39 && str[j] != 34)
		j++;
	if ((str[j] && str[j + 1] && ((str[j] == 34 && str[j + 1] == 34)
				|| (str[j] == 39 && str[j + 1] == 39))))
		prametr = NULL;
	else
		prametr = find_arg(str, i, j, envp);
	if (prametr == NULL && f == 0)
	{
		free(before);
		return (NULL);
	}
	after = ft_substr(str, j, ft_strlen(str) - j);
	rez = triple_join(before, prametr, after);
	return (rez);
}

void	arg_parce_flag(int *flag, char rez_j)
{
	if (rez_j == 34 && flag[1] == 0)
	{
		if (flag[0] == 0)
			flag[0] = 1;
		else if (flag[0] == 1)
			flag[0] = 0;
	}
	if (rez_j == 39 && flag[0] == 0)
	{
		if (flag[1] == 0)
			flag[1] = 1;
		else if (flag[1] == 1)
			flag[1] = 0;
	}
}

/* Производит поиск и вызывает функцию замены $ARG
 на переменные иди переменные окружения, так же обрабатыет
 частные случаи, связанные с '$' и его комбинациями
 со спец сиволами*/
char	*arg_parce(char *line, t_shell *glob)
{
	int		j;
	char	*rez;
	char	*tmp;
	int		flag[2];

	j = 0;
	flag[0] = 0;
	flag[1] = 0;
	rez = ft_strdup(line);
	while (rez[j])
	{
		arg_parce_flag(flag, rez[j]);
		if (rez[j] == '$' && flag[1] == 0 && rez[j + 1] && rez[j + 1] != ' ')
		{
			tmp = rez;
			rez = replace_var(tmp, j + 1, 0, glob->our_envp);
			if (rez == NULL)
				rez = replace_var(tmp, j + 1, 1, glob->var_mass);
			free(tmp);
			j = 0;
		}
		j++;
	}
	free(line);
	return (rez);
}
