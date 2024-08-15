/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:02:49 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 12:12:57 by endoliam         ###   ########lyon.fr   */
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
	while (start > 0 && isispace(s[start]))
		start--;
	if (start == 0 || (s[start] && isoperator(s[start]) && !is_quote(s[start])))
		return (false);
	return (true);
}
bool	is_after(char *s,  int start)
{
	start++;
	while (s[start] && isispace(s[start]))
		start++;
	if (!s[start] || (isoperator(s[start]) && s[start] != '<' && s[start] != '>' && !is_quote(s[start])))
		return (false);
	return (true);
}

int	find_redirection(t_lexer **lexer, char *s, int start, t_minishell mini)
{
	if (s[start + 1] && s[start + 1] != s[start] && is_after(s, start))
		init_redirection(lexer, s[start], 1, mini); 
	else if (s[start + 1] && s[start + 1] == s[start])
	{
		start++;
		if (s[start + 1] && s[start + 1] != s[start] && is_after(s, start))
			init_redirection(lexer, s[start], 2, mini);
		else
			return (exit_failure("syntax error near unexpected token"
						, s[start]));
	}
	else
		return (exit_failure("syntax error near unexpected token"
						, s[start]));
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
