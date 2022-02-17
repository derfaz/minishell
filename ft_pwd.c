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

char	*ft_pwd(void)
{
	char	*buf;

	buf = (char *) ft_calloc(PATH_MAX, sizeof(char));
	buf = getcwd(buf, PATH_MAX);
	buf[ft_strlen(buf)] = '\n';
	write(1, buf, ft_strlen(buf));
	g_var.stat_code = 0;
	return (buf);
}
