/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:32:15 by eosfryd           #+#    #+#             */
/*   Updated: 2021/08/04 20:01:59 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem;
	t_list	*nextelem;

	elem = *lst;
	while (elem)
	{
		nextelem = elem->next;
		ft_lstdelone(elem, del);
		elem = nextelem;
	}
	*lst = NULL;
}
