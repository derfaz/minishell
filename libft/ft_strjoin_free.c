/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:38:32 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:55:18 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int free1, int free2)
{
	char	*str;

	if (!s1)
	{
		s1 = "";
		free1 = 0;
	}
	if (!s2)
	{
		s2 = "";
		free2 = 0;
	}
	str = ft_strjoin(s1, s2);
	if (free1)
		ft_memdel((void **)(&s1));
	if (free2)
		ft_memdel((void **)(&s2));
	return (str);
}
