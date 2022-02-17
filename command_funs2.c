/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_funs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:38:42 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:38:42 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comma_token	*ft_commad(t_shell *glob, t_comma_token *tmp)
{
	g_var.pidie = INT_MIN;
	make_direction(0, tmp, glob, NULL);
	dup2(tmp->fd_out, 1);
	dup2(tmp->fd_in, 0);
	if (g_var.pidie == INT_MIN + 1 || g_var.pidie == INT_MIN)
		g_var.stat_code = 0;
	if (g_var.pidie != INT_MIN + 1 && g_var.pidie != INT_MIN + 2)
		def_command(tmp->arguments, glob);
	dup2(glob->std_out, 1);
	dup2(glob->std_in, 0);
	if (tmp->fd_in != 0)
		close(tmp->fd_in);
	if (tmp->fd_out != 1)
		close(tmp->fd_out);
	tmp = tmp->next;
	return (tmp);
}

void	wrapper(int pipefd[], t_shell *glob, t_comma_token *tmp, int flag[])
{
	pid_t	pid;

	pid = fork();
	if (flag[2] == 0)
		flag[0] = (int)pid;
	else
		flag[1] = (int)pid;
	if (pid == 0)
	{
		if (flag[2] == 0)
			dup2(pipefd[1], STDOUT_FILENO);
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
		}
		ft_commad(glob, tmp);
		exit(0);
	}
}

t_comma_token	*first_proc(t_shell *glob, t_comma_token *tmp, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_commad(glob, tmp);
		exit(g_var.stat_code);
	}
	return (tmp->next);
}

t_comma_token	*mid_proc(t_shell *glob,
						   t_comma_token *tmp, int **pipefd, int p)
{
	pid_t	pid;

	pipe(pipefd[p]);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[p - 1][1]);
		dup2(pipefd[p - 1][0], STDIN_FILENO);
		close(pipefd[p][0]);
		dup2(pipefd[p][1], STDOUT_FILENO);
		ft_commad(glob, tmp);
		exit(g_var.stat_code);
	}
	close(pipefd[p - 1][1]);
	close(pipefd[p - 1][0]);
	return (tmp->next);
}

t_comma_token	*last_proc(t_shell *glob, t_comma_token *tmp, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		ft_commad(glob, tmp);
		exit(g_var.stat_code);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (tmp->next);
}
