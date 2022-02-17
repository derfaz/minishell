/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:34:48 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:17:23 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		cc;
	char		*d;
	size_t		i;
	char		*s;

	cc = c;
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == cc)
			return ((void *)d + i + 1);
		i++;
	}
	return (NULL);
}
