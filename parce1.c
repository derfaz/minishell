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

/* Опираясь на листы соединяет два слова. 
Пример: 111'2121' будет объединен в 1112121 */
t_arg	*mergeargs(t_arg *arg, char **rez, int item)
{
	char	*tmp;

	tmp = NULL;
	if (arg->space == 1)
	{
		rez[item] = ft_strjoin(arg->args, arg->next->args);
		arg = arg->next;
		while (arg->space == 1)
		{
			tmp = rez[item];
			rez[item] = ft_strjoin(tmp, arg->next->args);
			arg = arg->next;
			if (tmp)
				free(tmp);
		}
	}
	else
		rez[item] = ft_strdup(arg->args);
	return (arg);
}

/* Преобразет список листов со словами в массив строк */
char	**post_parce(t_arg	*tmp, int len)
{
	char	**rez;
	int		item;
	t_arg	*temp;

	temp = tmp;
	while (tmp)
	{
		if (tmp->space == 0)
			len++;
		tmp = tmp->next;
	}
	if (!len)
		return (NULL);
	item = 0;
	rez = (char **)malloc(sizeof(char *) * (len + 1));
	tmp = temp;
	while (item < len)
	{
		tmp = mergeargs(tmp, rez, item);
		item++;
		tmp = tmp->next;
	}
	rez[len] = NULL;
	return (rez);
}

/* Отсоединяет от списка аргументов отдельный лист с редиректом,
а так же все последующие редиректу листы со словами, если те
должны будут в дальнейшем соединиться в один аргумент */
void	transfer_arg(t_arg	*new, t_alist *list, t_shell *glob)
{
	t_arg	*tmp;
	t_arg	*tmp2;

	if (new->prev == NULL)
		glob->arg_list->ahead = new->next;
	if (new->next)
		new->next->prev = new->prev;
	if (new->prev)
		new->prev->next = new->next;
	if (new->space == 1)
		tmp2 = new->next;
	new->next = NULL;
	new->prev = NULL;
	if (list->ahead == NULL)
		list->ahead = new;
	else
	{
		tmp = list->ahead;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	if (new->space == 1)
		transfer_arg(tmp2, list, glob);
}

/* Отсоединяет от списка листов те листы, в которых собдержатися редиректы,
формирует массив редиректов с соответсвующими им файлами */
char	**redir_handler(t_arg *arg, int flag, t_shell *glob)
{
	char	**rez;
	t_arg	*tmp;
	t_alist	*dirlist;

	dirlist = list_init();
	while (arg)
	{
		flag = 0;
		if ((arg->args[0] == '>' || arg->args[0] == '<') && arg->qoute == ' ')
		{
			tmp = arg;
			if (!arg->args[1])
				arg->space = 1;
			while (arg && arg->space == 1)
				arg = arg->next;
			flag = 1;
			arg = arg->next;
			transfer_arg(tmp, dirlist, glob);
		}
		if (arg && flag == 0)
			arg = arg->next;
	}
	rez = post_parce(dirlist->ahead, 0);
	free_a_list(dirlist);
	return (rez);
}

/* Производит замену $ARG в сторках 
на перемнные окружения или простые переменные */
void	mid_parce(t_shell *glob)
{
	t_arg	*tmp;

	tmp = glob->arg_list->ahead;
	while (tmp)
	{
		if (tmp->qoute != 39)
			tmp->args = arg_parce(tmp->args, glob);
		tmp = tmp->next;
	}
}
