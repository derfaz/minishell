/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_path_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:41:20 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 17:41:20 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*def_path_val(t_shell *glob)
{
	char	*buf;
	char	*path_val;
	char	*tmp;

	buf = (char *) ft_calloc(PATH_MAX, sizeof(char));
	buf = getcwd(buf, PATH_MAX);
	path_val = var_val("PATH", glob);
	tmp = ft_strjoin_free(path_val, ":", 0, 0);
	path_val = ft_strjoin_free(tmp, buf, 1, 1);
	return (path_val);
}
