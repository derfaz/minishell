/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:04:47 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:10:35 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ss;

	ss = NULL;
	while (*s)
	{
		if (*s == c)
			ss = (char *)s;
		s++;
	}
	if (c != '\0')
		return (ss);
	return ((char *)s);
}
