/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:09:48 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:17:07 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	char	*s;
	char	cc;
	size_t	i;

	cc = (char)c;
	s = (char *)src;
	i = 0;
	while (i < n)
	{
		if (s[i] == cc)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
