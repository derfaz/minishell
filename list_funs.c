/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:24:07 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 17:24:07 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Создает из аргументов функции лист под слово */
t_arg	*create_item(char *content, char quots, int z)
{
	t_arg	*itemnew;

	itemnew = (t_arg *)malloc(sizeof(t_arg));
	itemnew->next = NULL;
	itemnew->prev = NULL;
	itemnew->args = content;
	itemnew->qoute = quots;
	itemnew->space = z;
	return (itemnew);
}

void	add_new_arg(char *content, char quots, int z, t_alist *arg_list)
{
	t_arg	*tmp;
	t_arg	*new;

	new = create_item(content, quots, z);
	if (arg_list->ahead == NULL)
		arg_list->ahead = new;
	else
	{
		tmp = arg_list->ahead;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	arg_list->lenght++;
}

/* Иницирует отдельный лист */
t_alist	*list_init(void)
{
	t_alist	*list;

	list = (t_alist *)malloc(sizeof(t_alist));
	list->ahead = NULL;
	list->lenght = 0;
	return (list);
}

/* ft_isprint, не пропускающий пробел */
int	ft_is(int c)
{
	if (c < 33 || c > 126)
		return (0);
	return (1);
}

void	free_a_list(t_alist *list)
{
	t_arg	*tmp;
	t_arg	*tmp2;

	if (list->ahead)
	{
		tmp = list->ahead;
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2->args);
			free(tmp2);
		}
	}
	if (list)
		free(list);
}
