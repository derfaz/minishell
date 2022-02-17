/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstallfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:32:15 by eosfryd           #+#    #+#             */
/*   Updated: 2021/08/04 20:14:02 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstallfree(t_list **lst)
{
	t_list	*elem;
	t_list	*nextelem;

	elem = *lst;
	while (elem)
	{
		nextelem = elem->next;
		free(elem);
		elem = nextelem;
	}
	*lst = NULL;
}
