/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:23:52 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/22 15:36:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	lst_init_env(t_lexer **lexer, char *s, int start)
{
	t_lexer		*data;
	int			len;

	len = 0;
	data = NULL;
	while (s[start + len]
		&& !isispace(s[start + len]) && s[start + len] != '"')
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

static int	change_first_expand(char *contain, int i, t_lexer *lexer)
{
	int		len_exp;

	len_exp = 0;
	while (contain[len_exp] && !isispace(contain[len_exp]))
		len_exp++;
	lexer->contain = NULL;
	lexer->spaces = true;
	if (lexer->lex == DOUBLE_ENV)
		len_exp--;
	if (ft_strlen(contain) == 2 && lexer->lex == DOUBLE_ENV
		&& contain[0] == '"')
		lexer->contain = ft_qstrdup(contain);
	else
		lexer->contain = ft_substr(contain, i, len_exp);
	i = i + len_exp;
	return (i);
}

static	void	add_env_var(t_lexer *lexer, int i, int start)
{
	char	*contain;
	int		len;

	contain = ft_strdup(lexer->contain);
	len = ft_strlen(contain);
	if (lexer->lex == DOUBLE_ENV)
		len--;
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

t_lexer	*parsing_expand(t_lexer **lexer)
{
	int		i;
	int		start;
	t_lexer	*tmp;

	tmp = NULL;
	i = 0;
	start = 0;
	clean_expand((*lexer)->contain);
	if (!(*lexer)->contain || !*(*lexer)->contain)
	{
		tmp = (*lexer)->prev;
		free_one_lexer(lexer);
		if (tmp)
			tmp->next = NULL;
		return (tmp);
	}
	if (lexer && ((*lexer)->lex == ENV_VAR || (*lexer)->lex == DOUBLE_ENV))
	{
		if ((*lexer)->lex == DOUBLE_ENV)
			i++;
		add_env_var(*lexer, i, start);
	}
	return ((*lexer));
}
