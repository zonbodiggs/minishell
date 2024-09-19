/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:20:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/19 16:07:15 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_expand_quote(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		if (lexer && (lexer)->contain
			&& !ft_strcmp((lexer)->contain, "$")
			&& !lexer->spaces && lexer->lex == ENV_VAR)
		{
			if (((lexer)->next && (lexer)->next->lex == SINGLE_Q)
				|| ((lexer)->next && (lexer)->next->lex == DOUBLE_Q))
			{
				tmp = (lexer)->next;
				lexer = (lexer)->prev;
				free((lexer)->next->contain);
				free((lexer)->next);
				(lexer)->next = tmp;
			}
		}
		lexer = (lexer)->next;
	}
	return ;
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

char	*add_contain(t_lexer **lexer)
{
	char	*contain;

	if ((*lexer)->lex == DOUBLE_ENV)
	{
		contain = ft_qstrdup((*lexer)->contain);
		if (!contain || !*contain)
		{
			free((*lexer)->contain);
			(*lexer)->contain = NULL;
		}
	}
	else
		contain = ft_strdup((*lexer)->contain);
	return (contain);
}

void	expand_variable(t_lexer *data, t_lexer **lexer, t_minishell mini)
{
	if (data->lex == ENV_VAR || data->lex == DOUBLE_ENV)
	{
		if ((*lexer && ft_strcmp((*lexer)->contain, "<<")) || !*lexer)
			data->contain = init_env_var(data->contain, mini);
		else
		{
			if (data->lex == DOUBLE_ENV)
				data->lex = DOUBLE_Q;
			else
				data->lex = WORD;
		}
	}
}
