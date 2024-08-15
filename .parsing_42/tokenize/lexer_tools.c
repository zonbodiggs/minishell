/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:09:59 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 18:51:59 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_lexer(t_lexer **lexer, t_lexer *element)
{
	if (!element)
		return ;
	if (!*lexer)
	{
		*lexer = element;
		(*lexer)->prev = NULL;
		(*lexer)->next = NULL;
	}
	else
	{
		while ((*lexer)->next)
			*lexer = (*lexer)->next;
		(*lexer)->next = element;
		element->prev = *lexer;
		(*lexer) = (*lexer)->next;
		(*lexer)->next = NULL;
	}
}

int	lst_init_lexer(t_lexer **lexer, char *s, int start, t_minishell mini)
{
	t_lexer		*data;
	int			len;

	len = word_len(s + start);
	data = NULL;
	if (len <= 0)
		return (-1);
	data = ft_calloc(1, sizeof(t_lexer));
	if (!data)
		return (exit_failure("malloc allocation failed", 0));
	ft_memset(data, 0, sizeof(t_lexer));
	if (s[start + len] && s[start + len] == ' '
		&& final_space(s + start + len) == false)
		data->spaces = true;
	data->contain = ft_substr(s, start, len);
	if (!data->contain)
	{
		free(data);
		return (exit_failure("malloc allocation failed", 0));
	}
	init_lexer_type(data);
	if (data->lex == ENV_VAR || data->lex == DOUBLE_ENV)
		data->contain = init_env_var(data->contain, mini);
	add_lexer(lexer, data);
	return (start + len);
}

int	word_len(char *s)
{
	int		i;
	char	quote;

	if (!s)
		return (0);
	i = 0;
	quote = s[i];
	if ((s[i] == 39 || s[i] == '"'))
	{
		i = zap_quote(s, s[i], i + 1);
		if (i == 0)
			return (0);
		return (i + 1);
	}
	while (s[i] && isoperator(quote) == true)
		i++;
	while (s[i] && !isispace(s[i]) && isoperator(s[i]) == false)
		i++;
	return (i);
}
