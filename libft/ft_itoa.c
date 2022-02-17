/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:38:32 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:57:05 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int num)
{
	int		i;
	long	tenpow[35];

	tenpow[0] = 1;
	i = 0;
	while (num / tenpow[i])
	{
		tenpow[i + 1] = tenpow[i] * 10;
		i++;
	}
	return (i);
}

static char	*prnum(int nn, int llen, int ssign, char *dd)
{
	int		i;
	long	ttenpow[35];

	ttenpow[0] = 1;
	i = 0;
	while (nn / ttenpow[i])
	{
		ttenpow[i + 1] = ttenpow[i] * 10;
		i++;
	}
	while (i > 0)
	{
		dd[llen - i + ssign] = '0' + nn / ttenpow[i - 1];
		nn = nn - nn / ttenpow[i - 1] * ttenpow[i - 1];
		i--;
	}
	dd[llen + ssign] = '\0';
	return (dd);
}

static char	*limprint0(void)
{
	char	*d;

	d = (char *)malloc(sizeof(char) * 2);
	if (!d)
		return (NULL);
	d[0] = '0';
	d[1] = '\0';
	return (d);
}

static char	*limprint1(void)
{
	char	*d;

	d = (char *)malloc(sizeof(char) * 12);
	if (!d)
		return (NULL);
	d[0] = '-';
	d[1] = '2';
	d[2] = '1';
	d[3] = '4';
	d[4] = '7';
	d[5] = '4';
	d[6] = '8';
	d[7] = '3';
	d[8] = '6';
	d[9] = '4';
	d[10] = '8';
	d[11] = '\0';
	return (d);
}

char	*ft_itoa(int n)
{
	char	*d;
	int		sign;
	int		len;

	if (n == 0)
		return (limprint0());
	if (n < -2147483647)
		return (limprint1());
	else
	{
		if (n >= 0)
			sign = 0;
		else
		{
			n = -n;
			sign = 1;
		}
		len = numlen(n);
		d = (char *)malloc(sizeof(char) * (len + sign + 1));
		if (!d)
			return (NULL);
		if (sign == 1)
			d[0] = '-';
		return (prnum(n, len, sign, d));
	}
}
