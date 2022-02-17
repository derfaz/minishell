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

int	arg_exists(char **args)
{
	int	i;
	int	j;
	int	rez;

	i = 0;
	j = 0;
	rez = 0;
	while (args[i])
		i++;
	while (j < i)
	{
		if (args[j][0])
			rez = 1;
		j++;
	}
	return (rez);
}

char	*ft_echo2(char *str, int nl)
{
	if (nl)
		str = ft_strjoin_free(str, "\n", 1, 0);
	write(1, str, ft_strlen(str));
	return (str);
}

char	*ft_echo(char **args)
{
	int		nl;
	char	*str;

	nl = 1;
	if (!args || *args == 0 || arg_exists(args) == 0)
	{
		write(1, "\n", 1);
		return (ft_strdup("\n"));
	}
	if (!ft_strncmp(*args, "-n", 3))
	{
		nl = 0;
		while (!ft_strncmp(*args, "-n", 3))
			args++;
	}
	str = 0;
	while (*args && arg_exists(args))
	{
		if (str && str[0])
			str = ft_strjoin_free(str, " ", 1, 0);
		str = ft_strjoin_free(str, *args, 1, 0);
		args++;
	}
	return (ft_echo2(str, nl));
}
