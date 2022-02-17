/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:57:26 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:12:50 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clean(char **s)
{
	int		j;

	j = 0;
	while (s[j] != NULL)
	{
		free(s[j]);
		j++;
	}
	free(s[j]);
	free(s);
}

static int	ft_hmwords(char const *s, char c)
{
	int		rez;
	int		i;

	rez = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			rez++;
		i++;
	}
	return (rez);
}

static char	*ft_filler(char const *s, char c, int p)
{
	char	*rez;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while ((s[p - 1] != c) && (p))
	{
		len++;
		p--;
	}
	rez = (char *)malloc(sizeof(char) * (len + 1));
	if (rez == NULL)
		return (NULL);
	while (len-- != 0)
		rez[i++] = s[p++];
	rez[i] = '\0';
	return (rez);
}

static char	**ft_result(char **rez, char const *s, char c, int hmw)
{
	int		word;
	int		p;

	p = 0;
	word = 0;
	while ((word != hmw) && (s[p++]))
	{
		if ((s[p - 1] != c) && ((s[p] == '\0') || (s[p]) == c))
		{
			rez[word] = ft_filler(s, c, p);
			if (rez[word] == NULL)
			{
				ft_clean(rez);
				return (NULL);
			}
			word++;
		}
	}
	rez[hmw] = NULL;
	return (rez);
}

char	**ft_split(char const *s, char c)
{
	int		hmw;
	char	**rez;

	if (s == NULL)
		return (NULL);
	hmw = ft_hmwords(s, c);
	rez = malloc(sizeof(char *) * (hmw + 1));
	if (rez == NULL)
		return (NULL);
	return (ft_result(rez, s, c, hmw));
}
