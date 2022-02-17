/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:41:35 by eosfryd           #+#    #+#             */
/*   Updated: 2021/09/08 18:18:14 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

void	free_str_arr(char **arr)
{
	int	len;

	len = str_arr_len(arr);
	while (len)
	{
		free(arr[len - 1]);
		arr[len - 1] = 0;
		len--;
	}
}

void	printy_pie(char **a)
{
	int	i;

	i = 0;
	if (!a || !(*a))
		return ;
	while (a && a[i])
	{
		printf("%d string is: %s\n", i, a[i]);
		i++;
	}
}

void	display_str_arr(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
	{
		write(1, a[i], ft_strlen(a[i]));
		write(1, "\n", 1);
		i++;
	}
}

char	**cpy_str_arr(char **arg_arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = (char **) ft_calloc(str_arr_len(arg_arr) + 1, sizeof(char *));
	while (arg_arr && arg_arr[i])
	{
		new_arr[i] = arg_arr[i];
		i++;
	}
	return (new_arr);
}
