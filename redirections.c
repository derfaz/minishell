/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:38:36 by eosfryd           #+#    #+#             */
/*   Updated: 2021/09/09 13:29:20 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

char	*make_some_shield(char *line, t_shell *glob)
{
	int		j;
	char	*rez;
	char	*tmp;

	j = 0;
	rez = ft_strdup(line);
	while (rez[j])
	{
		if (rez[j] == '$' && rez[j + 1] && rez[j + 1] != ' ')
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
	j = 0;
	free(line);
	return (rez);
}

/* Реализация хердока */
void	ft_heredock(char *stopword, char *line, char *rez, t_shell *glob)
{
	int	flag;

	flag = 1;
	while (flag == 1 || ft_strcmp(line, stopword))
	{
		flag = 0;
		line = readline("> ");
		if (!ft_strcmp(line, stopword))
			break ;
		line = make_some_shield(line, glob);
		if (rez == NULL)
		{
			rez = ft_strdup(line);
			free(line);
		}
		else
			rez = triple_join(rez, ft_strdup("\n"), ft_strdup(line));
	}
	rez = triple_join(rez, ft_strdup("\n"), NULL);
	free(line);
	flag = open("left crutch", O_CREAT | O_WRONLY | \
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(flag, rez, ft_strlen(rez));
	close(flag);
}

void	heredock_wrapper(char *stopword, char *line, int *ret, t_shell *glob)
{
	char	*rez;

	rez = NULL;
	g_var.pidie = fork();
	if (g_var.pidie == 0)
	{
		ft_heredock(stopword, line, rez, glob);
		exit(0);
	}
	wait(NULL);
	if (g_var.pidie != INT_MIN && g_var.pidie != INT_MIN + 1)
		*ret = open("left crutch", O_RDONLY);
}

/* Открывает файл в соответвии с видом редиректа и возвращет его дискриптор */
int	open_by_name(char *name, char flag, t_shell *glob)
{
	int	rez;

	if (flag == '(')
		heredock_wrapper(name + 2, NULL, &rez, glob);
	else if (flag == '>')
		rez = open(name + 1, O_CREAT | O_WRONLY | \
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (flag == ')')
		rez = open(name + 2, O_CREAT | O_WRONLY | O_APPEND | \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		rez = open(name + 1, O_RDONLY);
	if (rez == -1)
	{
		printf("%s\n", strerror(errno));
		g_var.stat_code = 1;
		g_var.pidie = INT_MIN + 2;
	}
	return (rez);
}

/* Берет массив строк с редиректами и обрабатывает все их,
 меняет дискрипторы в соответсвии
с последними встретившимимся редиректами */
void	make_direction(int i, t_comma_token *comma, t_shell *glob, char **m)
{
	if (comma->direction)
	{
		m = comma->direction;
		while (m[i])
		{
			if (m[i][0] == '>')
			{
				if (comma->fd_out != 1)
					close(comma->fd_out);
				if (m[i][1] == '>')
					comma->fd_out = open_by_name(m[i++], ')', glob);
				else
					comma->fd_out = open_by_name(m[i++], '>', glob);
			}
			else
			{
				if (comma->fd_in != 0)
					close(comma->fd_in);
				if (m[i][1] == '<')
					comma->fd_in = open_by_name(m[i++], '(', glob);
				else
					comma->fd_in = open_by_name(m[i++], '<', glob);
			}
		}
	}
}
