/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:24:12 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:11:00 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	char	*rez;

	if ((NULL == s) || (NULL == f))
		return (NULL);
	size = (ft_strlen(s) + 1);
	rez = (char *)malloc(sizeof(char) * size);
	if (NULL == rez)
		return (NULL);
	size -= 2;
	rez[size + 1] = '\0';
	while (size >= 0)
	{
		rez[size] = f(size, s[size]);
		size -= 1;
	}
	return (rez);
}
