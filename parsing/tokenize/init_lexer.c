/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:51 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/21 18:50:37 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_redirection(t_lexer **lexer, char c, int flag)
{
	if (c == '<' && flag == 1)
		lst_init_lexer(lexer, "<", 0);
	else if (c == '>' && flag == 1)
		lst_init_lexer(lexer, ">", 0);
	else if (c == '<' && flag == 2)
		lst_init_lexer(lexer, "<<", 0);
	else if (c == '>' && flag == 2)
		lst_init_lexer(lexer, ">>", 0);
}

void	init_lexer_type(t_lexer *data)
{
	if (data->contain[0] == 39 && data->contain[1] == '$')
		data->lex = SINGLE_ENV;
	else if (data->contain[0] == '"' && data->contain[1] == '$')
		data->lex = DOUBLE_ENV;
	else if (data->contain[0] == 39)
		data->lex = SINGLE_Q;
	else if (data->contain[0] == '"')
		data->lex = DOUBLE_Q;
	else if (data->contain[0] == '|' && !data->contain[1])
		data->lex = PIPES;
	else if (getenv(data->contain) != 0)
		data->lex = ENV_VAR;
	else if (data->contain[0] == '<')
		data->lex = INPUT;
	else if (data->contain[0] == '>')
		data->lex = OUTPUT;
	else
		data->lex = WORD;
}

int	init_operator(t_lexer **lexer, char *s, int start)
{
	if (s[start] == '|')
	{
		if (s[start + 1] && s[start + 1] == '|')
			return (exit_failure("syntax error near unexpected symbol\n"));
		lst_init_lexer(lexer, "|", 0);
	}
	else if (s[start] == '<' || s[start] == '>')
	{
		if ((s[start + 1] && s[start + 1] != s[start]) || !s[start + 1])
			init_redirection(lexer, s[start], 1);
		else if (s[start + 1] && s[start + 1] == s[start])
		{
			if (s[start + 2] && s[start + 2] == s[start])
				return (exit_failure("syntax error near unexpected symbol\n"));
			else
				init_redirection(lexer, s[start], 2);
			start++;
		}
	}
	else
		start = lst_init_lexer(lexer, s, start) - 1;
	if (start < 0)
		return (exit_failure("error : quote don't closed\n"));
	return (start);
}

t_lexer		*create_lexer(char *s)
{
	int			i;
	t_lexer		*lexer;

	i = 0;
	lexer = NULL;
	while (s && s[i])
	{
		if (isword(s, i) == true)
			i = lst_init_lexer(&lexer, s, i); // allocation
		if (i < 0)
			break ; // free exit and break
		if (isoperator(s[i]) == true)
		{
			i = init_operator(&lexer, s, i);
			if (i < 0)
				break ; // free exit and break
			while (s[i] && s[i + 1] && s[i + 1] == ' ')
				i++;
		}
		if (s[i])
			i++;
	}
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}
