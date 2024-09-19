/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:58:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/29 11:44:16 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*find_expand(char *s)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	tmp = ft_strchr(s, '$');
	if (!tmp[i + 1] || (!ft_isalnum(tmp[i + 1]) && tmp[i + 1] != '?'))
	{
		tmp[i] = '$' * -1;
		if (tmp[i + 1] == '$')
			tmp[i + 1] = '$' * -1;
		res = ft_substr(tmp, 0, i + 1);
		return (res);
	}
	i++;
	if (tmp[i] == '?')
		res = ft_substr(tmp, 0, i + 1);
	else
	{
		while ((tmp[i] && !isispace(tmp[i]) && ft_isalnum(tmp[i])))
			i++;
		res = ft_substr(tmp, 0, i);
	}
	return (res);
}

bool	is_negative_content(char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == -36)
			return (true);
		i++;
	}
	return (false);
}

char	*free_expand(char *s)
{
	s = NULL;
	free(s);
	return (NULL);
}

char	*join_or_dup(char *s, char *var)
{
	char	*res;

	if (is_negative_content(var))
		res = ft_strjoin(s, var);
	else
		res = ft_strdup(s);
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
	if (!mygetenv(var + 1, mini))
		res = join_or_dup(s, var);
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
