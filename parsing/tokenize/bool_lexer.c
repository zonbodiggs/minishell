/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/20 11:34:55 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	isword(char *s, int start)
{
	if (isoperator(s[start]) == false)
	{
		if ((start > 0 && isoperator(s[start]) == false
				&& isoperator(s[start - 1]) == true)
			|| (start == 0 && s[start] != ' ')
			|| (start > 0 && s[start] != ' ' && s[start] != '|'
				&& s[start - 1] == ' ' ))
		return (true);	
	}
	return (false);
}

bool	final_space(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == ' ')
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
