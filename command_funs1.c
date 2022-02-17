/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_funs1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:38:33 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:38:33 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_our_command(char *cmd)
{
	char	**cmd_arr;
	char	**tmp;
	int		ret;

	cmd_arr = (char **) malloc(sizeof(char *) * 8);
	cmd_arr[0] = ft_strdup("echo");
	cmd_arr[1] = ft_strdup("env");
	cmd_arr[2] = ft_strdup("export");
	cmd_arr[3] = ft_strdup("unset");
	cmd_arr[4] = ft_strdup("exit");
	cmd_arr[5] = ft_strdup("pwd");
	cmd_arr[6] = ft_strdup("cd");
	cmd_arr[7] = 0;
	tmp = cmd_arr;
	ret = 0;
	while (*cmd_arr)
	{
		if (!ft_strncmp(*cmd_arr, cmd, ft_strlen(cmd) + 1))
			ret = 1;
		cmd_arr++;
	}
	ft_clean(tmp);
	return (ret);
}

void	exec_our_command(char **arg_arr, t_shell *glob)
{
	char	*rez;

	rez = NULL;
	if (!ft_strncmp(*arg_arr, "echo", ft_strlen(*arg_arr)))
		rez = ft_echo(arg_arr + 1);
	else if (!ft_strncmp(*arg_arr, "env", ft_strlen(*arg_arr)))
		display_str_arr(glob->our_envp);
	else if (!ft_strncmp(*arg_arr, "export", ft_strlen(*arg_arr)))
		ft_export(arg_arr + 1, glob);
	else if (!ft_strncmp(*arg_arr, "unset", ft_strlen(*arg_arr)))
		ft_unset(arg_arr + 1, glob);
	else if (!ft_strncmp(*arg_arr, "pwd", ft_strlen(*arg_arr)))
		rez = ft_pwd();
	else if (!ft_strncmp(*arg_arr, "cd", ft_strlen(*arg_arr)))
		ft_cd(arg_arr + 1, glob);
	else if (!ft_strncmp(*arg_arr, "exit", ft_strlen(*arg_arr)))
		ft_exit(arg_arr + 1);
	if (rez)
		free(rez);
}

void	def_command(char **arg_arr, t_shell *glob)
{
	if (arg_arr && *arg_arr)
	{
		if (is_our_command(*arg_arr))
			exec_our_command(arg_arr, glob);
		else
		{
			ft_execve(arg_arr, glob, NULL, NULL);
			g_var.stat_code /= 256;
		}
	}
	return ;
}

void	free_t_comma_token(t_comma_token *token)
{
	if (!token)
		return ;
	if (token->arguments && token->arguments[0])
		ft_clean(token->arguments);
	if (token->direction && token->direction[0])
		ft_clean(token->direction);
}

void	free_t_comma_list(t_comma_list *comma)
{
	t_comma_token	*tmp;
	t_comma_token	*tmp2;

	if (!comma)
		return ;
	if (comma->head)
	{
		tmp = comma->head;
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free_t_comma_token(tmp2);
			free(tmp2);
		}
	}
	free(comma);
}
