/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:47:06 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:01:40 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	finish;
	char	*rez;

	if ((!(s1)) || (!(set)))
		return (NULL);
	start = 0;
	finish = ft_strlen(s1);
	while (ft_strchr(set, s1[start]))
		++start;
	while (ft_strchr(set, s1[finish - 1]) && (start < (finish - 2)))
		--finish;
	if (start < (finish - 1))
	{
		rez = ft_substr(s1, start, (finish - start));
		if (!(rez))
			return (NULL);
	}
	else
	{
		rez = (char *)ft_calloc(1, sizeof(char));
		if (!(rez))
			return (NULL);
	}
	return (rez);
}
