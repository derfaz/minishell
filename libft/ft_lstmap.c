/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:11:15 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:17:50 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rez;
	t_list	*item;

	rez = NULL;
	while (lst)
	{
		item = ft_lstnew(f(lst->content));
		if ((item->content != lst->content) && (del != NULL))
			del(item->content);
		if (item == NULL)
			return (NULL);
		ft_lstadd_back(&rez, item);
		lst = lst->next;
	}
	return (rez);
}
