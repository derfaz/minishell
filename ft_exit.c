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

void	display_exir_err(char *arg)
{
	g_var.erstr = ft_strjoin("minishell: exit: ", arg);
	g_var.erstr = ft_strjoin_free
		(g_var.erstr, ": numeric argument required\n", 1, 0);
	printf("%s", g_var.erstr);
}

static size_t	def_exit_val(char *arg)
{
	long long	num;

	if (!*arg)
		return (0);
	if (!check_atoi_input(arg, "9223372036854775807"))
	{
		display_exir_err(arg);
		return (255);
	}
	num = ft_atoi_ll(arg);
	if (num >= 0)
		return (num % 256);
	while (num < 0)
		num += 256;
	return (num);
}

void	ft_exit2(int num_arg, char **arg_arr)
{
	int	val;

	if (!arg_arr || !*arg_arr)
		exit(0);
	else if (num_arg == 0 && *arg_arr)
	{
		display_exir_err(*arg_arr);
		exit (255);
	}
	else if (num_arg == 1)
	{
		if (!is_num(*arg_arr))
		{
			display_exir_err(*arg_arr);
			exit (0);
		}
		else
		{
			val = def_exit_val(*arg_arr);
			exit(val);
		}
	}
}

void	ft_exit3(char **arg_arr)
{
	if (!is_num(arg_arr[0]))
	{
		display_exir_err(*arg_arr);
		exit (255);
	}
	else
	{
		g_var.erstr = ft_strdup("minishell: exit: too many arguments\n");
		return ;
	}
}

void	ft_exit(char **arg_arr)
{
	int	i;
	int	num_arg;

	printf("exit\n");
	num_arg = 0;
	i = 0;
	while (arg_arr && arg_arr[i])
	{
		if (is_num(arg_arr[i]))
			num_arg++;
		i++;
	}
	if (num_arg > 1)
		return (ft_exit3(arg_arr));
	else
		return (ft_exit2(num_arg, arg_arr));
}
