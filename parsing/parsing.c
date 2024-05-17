/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:09 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/17 05:39:16 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	exit_failure(char *msg)
{
	ft_putstr_fd(msg, 2); // exit correctyl
	return ;
}

int	zap_quote(char *s, char quote, int i)
{
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] != quote)
		return (0);
	return (i);
}
// define len of sequence (quote pars)

int	word_len(char *s)
{
	int		i;
	char	quote;

	if (!s)
		return (0);
	i = 0;
	quote = s[i];
	if (quote == '|')
		i++;
	while (s[i] && s[i] != ' ' && s[i] != '|')
	{	
		if ((s[i] == 39  || s[i] == '"'))
		{	
			i = zap_quote(s, s[i], i + 1);
			if (i == 0)
			{
				exit_failure("error 2 : quote don't closed\n");
				return (0);
			}
		}
		i++;
	}
	return (i);
}
// add sequence too list
void	add_lexer(t_lexer **lexer, t_lexer *element)
{
	if (!*lexer)
	{
		*lexer = element;
		element->prev = NULL;
	}
	else
	{
		while ((*lexer)->next)
			*lexer = (*lexer)->next;
		(*lexer)->next = element;
		element->prev = *lexer;
		(*lexer) = (*lexer)->next;
	}
}
// tokenize
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
// init lexer of sequence

int	init_lexer(t_lexer **lexer, char *s, int start)
{
	t_lexer		*data;
	int			len;

	len = word_len(s + start);
	data = NULL;
	if (len == 0)
		return (-1);
	data = ft_calloc(1, sizeof(t_lexer));
	if (!data)
		exit_failure("malloc allocation failed\n");
	ft_memset(data, 0, sizeof(t_lexer));
	if (s[start + len] && s[start + len] == ' '
		&& final_space(s + start + len) == false)
		data->spaces = true;
	data->contain = ft_substr(s, start, len);
	init_lexer_type(data);
	printf("%s %d %d\n", data->contain, data->spaces, data->lex);
	if (!data->contain)
		exit_failure("malloc allocation failed\n");
	add_lexer(lexer, data);
	return (start + len);
}
// for check sequence of char

bool	isword(char *s, int start)
{
	if ((start > 0 && s[start] != '|' && s[start - 1] == '|' )
		|| (start == 0 && s[start] != ' ')
		|| (start > 0 && s[start] != ' '  && s[start] != '|'
			&& s[start - 1] == ' ' )
		|| (start > 0 && s[start] == '|' && s[start - 1] == ' '
			&& s[start + 1] == ' '))
		return (true);
	return (false);
}
// init lexer
void	create_lexer(char *s)
{
	int			i;
	t_lexer		*lexer;

	i = 0;
	lexer = NULL;
	while(s && s[i])
	{
		if (isword(s, i) == true)
		{
			i = init_lexer(&lexer, s, i); // protect init
			if (i < 0)
				break ;
		}
		if ((s[i] == '|' && s[i + 1] != ' ')
			|| (s[i] == '|' && s[i - 1] != ' '))
		{
			if (s[i + 1] == '|')
			{
				exit_failure("syntax error near unexpected symbol\n");
				break; 
			}
			init_lexer(&lexer, "|", 0);
			if (s[i + 1] == ' ')
				i++;
		}
		if (s[i])
			i++;
	}
}
