/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:22:57 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 16:10:14 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_ll(long long int n)
{
	char			*num;
	long long int	size;
	long long int	first;

	size = 1;
	first = n;
	if (n < 0)
		size++;
	size = size + ft_len(first, 10);
	num = (char *)malloc((size + 1) * sizeof(char));
	if (num == (NULL))
		return (NULL);
	num[size] = '\0';
	if (n < 0)
	{
		num[0] = '-';
		num[--size] = -(n % 10) + '0';
		n = n / -10 + 0 * first++;
	}
	while (--size >= first)
	{
		num[size] = n % 10 + '0';
		n = n / 10;
	}
	return (num);
}
