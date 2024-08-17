/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:51 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/16 22:35:50 by endoliam         ###   ########lyon.fr   */
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

int	create_operator(t_lexer **lexer, char *s, int i, t_minishell mini)
{
	i = init_operator(lexer, s, i, mini);
	if (i < 0)
		return (-1);
	if (s[i] && isispace(s[i])
		&& final_space(s + i) == false)
		(*lexer)->spaces = true;
	while (s[i] && s[i + 1] && isispace(s[i + 1]))
		i++;
	return (i);
}
int	lst_init_env(t_lexer **lexer, char *s, int start)
{
	t_lexer		*data;
	int			len;

	len = 0;
	data = NULL;
	while (s[start + len] && !isispace(s[start + len])&& s[start + len] != '"')
		len++;
	if (len <= 0)
		return (-1);
	data = ft_calloc(1, sizeof(t_lexer));
	if (!data)
		return (exit_failure("malloc allocation failed", 0));
	ft_memset(data, 0, sizeof(t_lexer));
	data->spaces = true;
	data->contain = ft_substr(s, start, len);
	if (!data->contain)
	{
		free(data);
		return (exit_failure("malloc allocation failed", 0));
	}
	data->lex = WORD;
	add_lexer(lexer, data);
	return (start + len);
}
int	change_first_expand(char *contain, int i, t_lexer *lexer)
{
	int		len_exp;

	len_exp = 0;
	while (contain[len_exp] && !isispace(contain[len_exp]))
			len_exp++;
	lexer->contain = NULL;
	lexer->spaces = true;
	if (lexer->lex == DOUBLE_ENV)
		len_exp--;
	if (ft_strlen(contain) == 2 && lexer->lex == DOUBLE_ENV && contain[0] =='"')
		lexer->contain = ft_qstrdup(contain);
	else
		lexer->contain = ft_substr(contain, i, len_exp);
	i = i + len_exp;
	return (i);
}

void	parsing_expand(t_lexer *lexer)
{
	int		i;
	int 	start;
	char	*contain;
	int		len;

	i = 0;
	start = 0;
	if (lexer && (lexer->lex == ENV_VAR || lexer->lex == DOUBLE_ENV))
	{
		contain = ft_strdup(lexer->contain);
		len = ft_strlen(contain);
		if (lexer->lex == DOUBLE_ENV)
		{
			i++;
			len--;
		}
		while (i <= len && contain[i])
		{
			if ((i == 0 && !isispace(contain[i]))
				|| (i > 0 && !isispace(contain[i] && isispace(contain[i - 1])))
				|| (i == 1 && !isispace(contain[i]) && contain[0] == '"'))
			{
				if (start == 0)
				{
					free(lexer->contain);
					i = change_first_expand(contain, i, lexer);
					start++;
				}
				else
					i = lst_init_env(&lexer, contain, i);
			}
			i++;
		}
		free(contain);
	}
	return ;
}

t_lexer	*create_lexer(char *s, t_minishell *mini)
{
	int			i;
	t_lexer		*lexer;

	i = 0;
	lexer = NULL;
	while (s && s[i])
	{
		if (isword(s, i) == true)
			i = lst_init_lexer(&lexer, s, i, *mini);
		if (i < 0)
			return (lexer_error_exit(i, lexer, mini));
		if (isoperator(s[i]) == true)
		{
			i = create_operator(&lexer, s, i, *mini);
			if (i < 0)
				return (lexer_error_exit(i, lexer, mini));
		}
		parsing_expand(lexer);
		if (s[i])
			i++;
	}
	free(s);
	lexer = get_start(lexer);
	return (lexer);
}
