/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 18:45:15 by eosfryd           #+#    #+#             */
/*   Updated: 2021/04/13 15:52:27 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*oddo(char **odd, char **line)
{
	char		*new;

	new = NULL;
	if (*odd)
	{
		new = ft_strchr(*odd, '\n');
		if (new)
		{
			*new = '\0';
			*line = ft_strdup(*odd);
			*odd = ft_strcpy(*odd, ++new);
		}
		else
		{
			*line = ft_strdup(*odd);
			*odd[0] = '\0';
		}
	}
	else
	{
		*line = (char *)malloc(sizeof(char));
		if (*line)
			*line[0] = '\0';
	}
	return (new);
}

static int	ft_return(int hmc, char **line, char *new, char **odd)
{
	if (hmc < 0 || !(*line))
	{
		ft_clean_str_by_adress(odd);
		ft_clean_str_by_adress(line);
		return (-1);
	}
	else if (hmc || new)
		return (1);
	else
	{
		ft_clean_str_by_adress(odd);
		return (0);
	}
}

static char	*newline(char *buff, char **odd)
{
	char		*new;

	new = NULL;
	new = ft_strchr(buff, '\n');
	if (new)
	{
		*new = '\0';
		ft_clean_str_by_adress(odd);
		*odd = ft_strdup(++new);
	}
	return (new);
}

static int	aaa(int *hmc, int fd, char *buff)
{
	int	rez;

	*hmc = read(fd, buff, BUFFER_SIZE);
	rez = *hmc;
	return (rez);
}

int	get_next_line(int fd, char **line)
{
	int			hmc;
	char		buff[BUFFER_SIZE + 1];
	char		*new;
	char		*cl;
	static char	*odd[1024];

	hmc = 0;
	if ((fd < 0) || !(line) || (BUFFER_SIZE <= 0))
		return (-1);
	new = oddo(&odd[fd], line);
	if (!(*line))
	{
		ft_clean_str_by_adress(&odd[fd]);
		return (-1);
	}
	while (!new && (aaa(&hmc, fd, buff)) > 0)
	{
		buff[hmc] = '\0';
		new = newline(buff, &odd[fd]);
		cl = *line;
		*line = ft_strjoin(*line, buff);
		free(cl);
	}
	return (ft_return(hmc, line, new, &odd[fd]));
}
