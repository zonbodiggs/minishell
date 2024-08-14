/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:02:49 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 18:41:56 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_redirection(t_lexer **lexer, char c, int flag, t_minishell mini)
{
	if (c == '<' && flag == 1)
		lst_init_lexer(lexer, "<", 0, mini);
	else if (c == '>' && flag == 1)
		lst_init_lexer(lexer, ">", 0, mini);
	else if (c == '<' && flag == 2)
		lst_init_lexer(lexer, "<<", 0, mini);
	else if (c == '>' && flag == 2)
		lst_init_lexer(lexer, ">>", 0, mini);
}

bool	is_before(char *s, int start)
{
	start--;
	while (start >= 0 && s[start])
	{
		if (!isispace(s[start]))
			return(true);
		start--;
	}
	return (false);
}
bool	is_after(char *s,  int start)
{
	start++;
	while (s[start])
	{
		if (!isispace(s[start]))
			return(true);
		start++;
	}
	return (false);
}

int	find_redirection(t_lexer **lexer, char *s, int start, t_minishell mini)
{
	if (!is_after(s, start))
		return (exit_failure("syntax error near unexpected token"
					, s[start]));
	if (s[start + 1] && s[start + 1] != s[start])
		init_redirection(lexer, s[start], 1, mini);
	else if (s[start + 1] && s[start + 1] == s[start])
	{
		if (!s[start + 2] || (s[start + 2] && s[start + 2] == s[start]))
			return (exit_failure("syntax error near unexpected token"
					, s[start]));
		else
			init_redirection(lexer, s[start], 2, mini);
		start++;
	}
	return (start);
}

int	init_operator(t_lexer **lexer, char *s, int start, t_minishell mini)
{
	char	c;

	c = s[start];
	if (!s[start + 1])
		return (exit_failure("syntax error near unexpected token", c));
	if (c == '|')
	{
		if (!is_after(s, start) || !is_before(s, start))
			return (exit_failure("syntax error near unexpected token", c));
		if (!s[start + 1] || (s[start + 1] && s[start + 1] == '|'))
			return (exit_failure("syntax error near unexpected token", c));
		lst_init_lexer(lexer, "|", 0, mini);
	}
	else if (c == '<' || c == '>')
		start = find_redirection(lexer, s, start, mini);
	else
		start = lst_init_lexer(lexer, s, start, mini) - 1;
	if (start < 0 && c == 39)
		return (exit_failure("quote don't closed", c));
	return (start);
}
