/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:08:17 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:13:01 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void		*tmp;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return ((malloc(size)));
	else
	{
		tmp = malloc(size);
		ft_memcpy(tmp, ptr, size);
		free(ptr);
		return (tmp);
	}
}
