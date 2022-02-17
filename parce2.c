/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:39:37 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:39:37 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Создает из аргументов функции лист под слово */
t_comma_token	*create_comma_item(char **content, char **content2, int ipipe)
{
	t_comma_token	*itemnew;

	itemnew = (t_comma_token *)malloc(sizeof(t_comma_token));
	itemnew->next = NULL;
	itemnew->prew = NULL;
	itemnew->arguments = content;
	itemnew->direction = content2;
	itemnew->fd_in = STDIN_FILENO;
	itemnew->fd_out = STDOUT_FILENO;
	itemnew->ipipe = ipipe;
	return (itemnew);
}

/* Создает из аргументов функции лист под слово. 
Добавляет его в список листов */
void	add_new_comma_arg(t_comma_list *l, char **c, char **d, int p)
{
	t_comma_token	*tmp;
	t_comma_token	*new;

	new = create_comma_item(c, d, p);
	if (l->head == NULL)
		l->head = new;
	else
	{
		tmp = l->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prew = tmp;
	}
	l->len++;
}

size_t	ft_strlen_mod(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '|')
		i++;
	return (i);
}

int	very_long_if(t_arg *tmp, int i)
{
	if (tmp->args && tmp->args[0] && \
	(tmp->args[0] == '<' || tmp->args[0] == '>') && !tmp->args[1] && tmp->next \
	&& tmp->next->args && tmp->next->args[0] && tmp->next->args[0] != '<' && \
	tmp->next->args[0] != '>')
		return (1);
	if (tmp->args && tmp->args[0] && tmp->args[1] && \
	((tmp->args[0] == '<' && tmp->args[1] == '<') \
	|| (tmp->args[0] == '>' && tmp->args[1] == '>')) \
	&& !tmp->args[2] && tmp->next && tmp->next->args && tmp->next->args[0] \
	&& tmp->next->args[0] != '<' && tmp->next->args[0] != '>')
		return (1);
	return (i);
}

int	arg_checker(t_alist *list)
{
	t_arg	*tmp;

	if (list && list->ahead)
	{
		tmp = list->ahead;
		while (tmp)
		{
			tmp->space = very_long_if(tmp, tmp->space);
			if (tmp->space == 0 && \
			((tmp->args[0] == '<' && !tmp->args[1]) || (tmp->args[0] == '>' \
			&& !tmp->args[1]) || (tmp->args[0] == '<' && tmp->args[1] == '<' \
			&& !tmp->args[2]) || (tmp->args[0] == '>' && tmp->args[1] == '>' \
			&& !tmp->args[2]) || (tmp->args[0] == '<' && !tmp->args[1])))
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}
