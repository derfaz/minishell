/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:29:44 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:55:09 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *dest, size_t len)
{
	char	*pb;

	pb = dest;
	while (len--)
		*pb++ = '\0';
	return (dest);
}
