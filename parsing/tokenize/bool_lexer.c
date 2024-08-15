/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 12:12:23 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	isispace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

bool	isword(char *s, int start)
{
	if (isoperator(s[start]) == false)
	{
		if ((start > 0 && isoperator(s[start]) == false
				&& isoperator(s[start - 1]) == true)
			|| (start == 0 && !isispace(s[start]))
			|| (start > 0 && !isispace(s[start]) && s[start] != '|'
				&& !isispace(s[start])))
			return (true);
	}
	return (false);
}

bool	final_space(char *s)
{
	int		i;

	i = 0;
	while (s[i] && isispace(s[i]))
		i++;
	if (!s[i])
		return (true);
	return (false);
}

bool	isoperator(char c)
{
	if ((c == '|')
		|| (c == '>')
		|| (c == '<')
		|| (c == 39)
		|| (c == '"'))
		return (true);
	return (false);
}
bool	is_quote(char c)
{
	if ((c == 39) || (c == '"'))
		return (true);
	return (false);
}

bool	is_env_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
