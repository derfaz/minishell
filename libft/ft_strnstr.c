/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:04:47 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:10:50 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	char	*rez;

	if (!haystack)
		return (NULL);
	i = 0;
	rez = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (rez);
	while (haystack[i] && (i < (int)len))
	{
		j = 0;
		while ((needle[j] == haystack[i + j]) && ((i + j) < (int)len))
		{
			if (!(needle[j + 1]))
				return (rez + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
