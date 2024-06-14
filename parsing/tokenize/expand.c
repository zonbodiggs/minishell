/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:58:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/11 19:21:51 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char 	*join_and_free(char *s1, char *s2)
{
	char 	*res;
	
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*find_expand(char *s)
{
	int i = 0;
	char	*tmp;
	char	*res;

	tmp = ft_strchr(s, '$');
	while (tmp[i] && tmp[i] != ' '&& tmp[i] != '"' )
		i++;
	res = ft_substr(tmp, 0, i);
	return (res);
}

char	*init_env_var(char *s)
{
	char 	*dollar;
	char	*tmp;
	char	*res;

	tmp = ft_strdup(s);
	dollar = find_expand(tmp);
	s[ft_strlen(s) - ft_strlen(ft_strchr(s, '$'))] = '\0';
	if (!getenv(dollar + 1) && ft_strlen(s) - ft_strlen(dollar) == 0)
	{
		s = NULL;
		free(s);
		return (NULL);
	}
	if (!getenv(dollar + 1))
		res = ft_strdup(s);
	else
		res = ft_strjoin(s, getenv(dollar + 1));
	if (tmp[ft_strlen(s) + ft_strlen(dollar)])
		res = join_and_free(res, tmp + ft_strlen(dollar) + ft_strlen(s));
	free(tmp);
	free(s);
	free(dollar);
	return (res);
}
