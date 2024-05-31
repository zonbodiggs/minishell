/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:51 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/31 16:07:49 by endoliam         ###   ########lyon.fr   */
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
	char	c;

	c = s[start];
	if (c == '|')
	{
		if (s[start + 1] && s[start + 1] == '|')
			return (exit_failure("syntax error near unexpected symbol", c));
		lst_init_lexer(lexer, "|", 0);
	}
	else if (c == '<' || c == '>')
	{
		if ((s[start + 1] && s[start + 1] != c) || !s[start + 1])
			init_redirection(lexer, c, 1);
		else if (s[start + 1] && s[start + 1] == c)
		{
			if (s[start + 2] && s[start + 2] == s[start])
				return (exit_failure("syntax error near unexpected symbol", c));
			else
				init_redirection(lexer, s[start], 2);
			start++;
		}
	}
	else
		start = lst_init_lexer(lexer, s, start) - 1;
	if (start < 0)
		return (exit_failure("error : quote don't closed", c));
	return (start);
}
t_lexer *get_start(t_lexer *lexer)
{
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}
t_lexer		*free_lexer(t_lexer *lex)
{
	t_lexer	*tmp;

	lex = get_start(lex);
	while (lex)
	{
		tmp = lex;
		if (lex->contain)
			free(lex->contain);
		lex = lex->next;
		free(tmp);
	}
	return (NULL);
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
			return (free_lexer(lexer)); // free exit and break
		if (isoperator(s[i]) == true)
		{
			i = init_operator(&lexer, s, i);
			if (i < 0)
				return (free_lexer(lexer)); // free exit and break
			while (s[i] && s[i + 1] && s[i + 1] == ' ')
				i++;
		}
		if (s[i])
			i++;
	}
	lexer = get_start(lexer);
	return (lexer);
}
