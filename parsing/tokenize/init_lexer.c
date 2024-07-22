/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:51 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/18 17:27:26 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_lexer_type(t_lexer *data)
{
	if (data->contain[0] == 39 && is_env_var(data->contain) == true)
		data->lex = SINGLE_ENV;
	else if (data->contain[0] == '"' && is_env_var(data->contain) == true)
		data->lex = DOUBLE_ENV;
	else if (data->contain[0] == 39)
		data->lex = SINGLE_Q;
	else if (data->contain[0] == '"')
		data->lex = DOUBLE_Q;
	else if (data->contain[0] == '|' && !data->contain[1])
		data->lex = PIPES;
	else if (is_env_var(data->contain) == true)
		data->lex = ENV_VAR;
	else if (data->contain[0] == '<')
		data->lex = INPUT;
	else if (data->contain[0] == '>')
		data->lex = OUTPUT;
	else
		data->lex = WORD;
}

t_lexer	*get_start(t_lexer *lexer)
{
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

int	create_operator(t_lexer *lexer, char *s, int i, t_minishell mini)
{
	i = init_operator(&lexer, s, i, mini);
	if (i < 0)
		return (-1);
	if (s[i] && s[i] == ' '
		&& final_space(s + i) == false)
		lexer->spaces = true;
	while (s[i] && s[i + 1] && s[i + 1] == ' ')
		i++;
	return (i);
}

t_lexer	*create_lexer(char *s, t_minishell mini)
{
	int			i;
	t_lexer		*lexer;

	i = 0;
	lexer = NULL;
	while (s && s[i])
	{
		if (isword(s, i) == true)
			i = lst_init_lexer(&lexer, s, i, mini);
		if (i < 0)
			return (free_lexer(&lexer));
		if (isoperator(s[i]) == true)
		{
			i = create_operator(lexer, s, i, mini);
			if (i < 0)
				return (free_lexer(&lexer));
		}
		if (s[i])
			i++;
	}
	free(s);
	lexer = get_start(lexer);
	return (lexer);
}
