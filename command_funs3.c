/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_funs3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:38:49 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:38:49 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comma_token	*make_pipe(t_shell *glob, t_comma_token *tmp, int num_p)
{
	int				**pipefd;
	int				p;
	int				i;

	p = 0;
	i = num_p + 1;
	pipefd = malloc(sizeof(int *) * num_p);
	while (p < num_p)
		pipefd[p++] = malloc(sizeof(int) * 2);
	p = 0;
	pipe(pipefd[p]);
	tmp = first_proc(glob, tmp, pipefd[p]);
	while (tmp && tmp->ipipe == 1)
		tmp = mid_proc(glob, tmp, pipefd, ++p);
	tmp = last_proc(glob, tmp, pipefd[p]);
	while (i--)
		wait(&g_var.stat_code);
	dup2(glob->std_out, 1);
	dup2(glob->std_in, 0);
	num_p--;
	while (num_p >= 0)
		free(pipefd[num_p--]);
	free(pipefd);
	g_var.stat_code /= 256;
	return (tmp);
}

void	check_code_diff(t_shell *glob)
{
	char	*str2;

	str2 = ft_strjoin_free("?=", g_var.code, 0, 0);
	if (ft_strncmp(var_val("?", glob), g_var.code, ft_strlen(str2) + 1))
		change_var(str2, glob);
	free(str2);
	if (g_var.erstr)
		kill(getpid(), SIGUSR1);
}

void	wrapper_comma_init(t_comma_list *comma, t_shell *glob)
{
	t_comma_token	*tmp;
	t_comma_token	*tmp2;
	int				num_p;

	num_p = 0;
	if (comma && comma->head)
	{
		tmp = comma->head;
		while (tmp)
		{
			if (tmp->ipipe == 1)
			{
				tmp2 = tmp;
				while (tmp2 && tmp2->ipipe == 1)
				{
					num_p++;
					tmp2 = tmp2->next;
				}
				tmp = make_pipe(glob, tmp, num_p);
			}
			else
				tmp = ft_commad(glob, tmp);
			check_code_diff(glob);
		}
	}
}
