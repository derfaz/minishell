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
/*
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
}*/

void	what_if(char *l, int *j, t_shell *glob)
{
	int	i;

	i = *j;
	if (l[i] && l[i] != ' ' && l[i] != '\0' && l[i] != '|')
	{
		if (l[i] == 34 || l[i] == 39)
			*j = argreader_q(i, l[i], l, glob);
		else
			*j = argreader_s(i, ' ', l, glob);
	}
}

int	parce_body(char *l, int i, t_comma_list *rez, t_shell *glob)
{
	int	len;
	int	ipipe;

	ipipe = 0;
	len = ft_strlen_mod(l);
	glob->arg_list = list_init();
	while (i < len && l[i] && l[i] != '|')
	{
		what_if(l, &i, glob);
		if (i < len && (l[i] == '|' || l[i + 1] == '|'))
			ipipe = 1;
		i++;
	}
	if (!arg_checker(glob->arg_list))
	{
		printf("syntax error\n");
		free(glob->arg_list);
		return (-1);
	}
	mid_parce(glob);
	glob->redir = redir_handler(glob->arg_list->ahead, 0, glob);
	glob->arg_mass = post_parce(glob->arg_list->ahead, 0);
	add_new_comma_arg(rez, glob->arg_mass, glob->redir, ipipe);
	free_a_list(glob->arg_list);
	return (i);
}

/* Собирает воедино все части парсера и на выходе выдает список листов,
в каждом киз которых будет своя команда со всеми необходимостями */
t_comma_list	*parce(char *line, t_shell *glob)
{
	int				item;
	t_comma_list	*rez;
	int				len;
	int				tmp;

	rez = (t_comma_list *)malloc(sizeof(t_comma_list));
	rez->head = NULL;
	rez->len = 0;
	item = 0;
	tmp = 0;
	len = ft_strlen(line);
	while (item < len && line[item] && line[item] != '|')
	{
		tmp = parce_body(line + item, 0, rez, glob);
		if (tmp == -1)
		{
			free_t_comma_list(rez);
			return (NULL);
		}
		item = item + tmp;
		if ((item < len) && line[item] == '|')
			item++;
	}
	return (rez);
}
