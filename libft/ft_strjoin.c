/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:22:08 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:11:34 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		item;
	int		jtem;
	char	*dest;
	char	*tsed;

	if ((!(s1)) || (!(s2)))
		return (NULL);
	item = ft_strlen((char *)s1);
	jtem = ft_strlen((char *)s2);
	dest = (char *)malloc(1 + jtem + item);
	if (NULL == dest)
		return (NULL);
	tsed = dest;
	while (*s1)
		*tsed++ = *s1++;
	while (*s2)
		*tsed++ = *s2++;
	*tsed = '\0';
	return (dest);
}
