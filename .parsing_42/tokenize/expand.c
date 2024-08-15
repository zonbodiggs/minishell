/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:58:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 15:46:44 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	if (!res)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	free(s1);
	return (res);
}

static char	*find_expand(char *s)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	tmp = ft_strchr(s, '$');
	i++;
	while (tmp[i] && !isispace(tmp[i]) && tmp[i] != '"'
		&& tmp[i] != 39 && tmp[i] != '$')
		i++;
	res = ft_substr(tmp, 0, i);
	return (res);
}

char	*init_env_var(char *s, t_minishell mini)
{
	char	*var;
	char	*tmp;
	char	*res;

	tmp = ft_strdup(s);
	var = find_expand(tmp);
	s[ft_strlen(s) - ft_strlen(ft_strchr(s, '$'))] = '\0';
	if (!mygetenv(var + 1, mini) && ft_strlen(s) - ft_strlen(var) == 0)
	{
		s = NULL;
		free(s);
		return (NULL);
	}
	if (!mygetenv(var + 1, mini))
		res = ft_strdup(s);
	else
		res = ft_strjoin(s, mygetenv(var + 1, mini));
	if (tmp[ft_strlen(s) + ft_strlen(var)])
		res = join_and_free(res, tmp + ft_strlen(var) + ft_strlen(s));
	free(tmp);
	free(s);
	free(var);
	if (ft_strchr(res, '$'))
		res = init_env_var(res, mini);
	return (res);
}
