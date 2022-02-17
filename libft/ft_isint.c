/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:36:35 by eosfryd           #+#    #+#             */
/*   Updated: 2021/08/22 17:07:59 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	long long int	rez;
	int				flag;

	rez = 0;
	flag = 1;
	while ((*str == ' ') || (*str == '\n') || (*str == '\f') \
	|| (*str == '\t') || (*str == '\v') || (*str == '\r'))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		rez = ((rez * 10) + (*str++ - '0'));
		if ((rez * flag) > INT_MAX || (rez * flag) < INT_MIN)
			return (0);
	}
	return (1);
}
