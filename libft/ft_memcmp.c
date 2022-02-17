/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:34:48 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:17:02 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *dst, const void *src, size_t n)
{
	const char	*d;
	const char	*s;

	d = dst;
	s = src;
	while (n--)
	{
		if (*d != *s)
			return ((unsigned char)*d - (unsigned char)*s);
		d++;
		s++;
	}
	return (0);
}
