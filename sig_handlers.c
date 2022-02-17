/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:39:46 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:39:46 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc(int sig)
{
	if (sig)
		sig++;
	if (g_var.pidie != INT_MIN && g_var.pidie != (INT_MIN + 1))
	{
		if (g_var.pidie == 0)
		{
			puts("");
			exit(0);
		}
		g_var.pidie = INT_MIN + 1;
	}
	else if (wait(NULL) == -1)
		printf("\bminishell$   \nminishell$ ");
}

void	ctrlslash(int sig)
{
	if (sig)
		sig++;
	printf("\bminishell$   \rminishell$ ");
}

void	sigusr1_handler(int sig)
{
	if (sig)
		sig++;
	write(1, g_var.erstr, ft_strlen(g_var.erstr));
	ft_memdel((void **)(&(g_var.erstr)));
}
