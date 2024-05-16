/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:09 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 15:28:06 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_failure(char *msg)
{
	printf("error : %s\n", msg);
	exit(2);
}

int		zap_quote(char *s, char quote, int i)
{
	while (s[i] && s[i] != quote)
		i++;
	return(i);
}

int		word_len(char *s)
{
	int		i;
	char	quote;

	if(!s)
		return(0);
	i = 0;
	quote = s[i];
	if (quote == 39 || quote == '"')
	{
		i = zap_quote(s, s[i], i + 1);
		if (s[i] != quote)
			exit_failure("quote don't closed");
		return(i + 1);
	}
	while(s[i] && s[i] != ' ')
		i++;
	return(i);
}

void	add_lexer(t_lexer **lexer, t_lexer *element)
{
	if (!*lexer)
	{
		*lexer = element;
		element->prev = NULL;
	}
	else
	{
		while((*lexer)->next)
			*lexer = (*lexer)->next;
		(*lexer)->next = element;
		element->prev = *lexer;
		(*lexer) = (*lexer)->next;
	}
}

void	init_lexer(t_lexer **lexer, char *s, int start)
{
	t_lexer		*data;
	int			len;

	len = word_len(s + start);
	if (!len)
		exit (40);
	data = ft_calloc(1, sizeof(t_lexer));
	data->next = NULL;
	data->prev = NULL;
	if (s[start + len] && s[start + len] == ' ')
		data->spaces = true;
	data->contain = ft_substr(s, start, len);
	printf("%s %d %c\n", data->contain, data->spaces,  s[start + len]);
	if (!data->contain)
		exit_failure("MALLOC FAILED");
	add_lexer(lexer, data);
}

void	create_lexer(char *s)
{
	int			i;
	char		quote;
	t_lexer		*lexer;

	i = 0;
	quote = 0;
	lexer = NULL;
	while(s[i])
	{
		if ((i > 0 && s[i] != ' ' && s[i - 1] == ' ' ) 
			|| (i == 0 && s[i] != ' '))
		{
			init_lexer(&lexer, s, i);
			if (s[i] == 39 || s[i] == '"')
				i = zap_quote(s, s[i], i + 1);
		}
			i++;
	}
}
