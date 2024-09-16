/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:23:52 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/09 13:02:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	lst_init_env(t_lexer **lexer, char *s, int start)
{
	t_lexer		*data;
	int			len;

	len = 0;
	data = NULL;
	while (start + len <= (int)ft_strlen(s)
		&& s[start + len] && !isispace(s[start + len]))
		len++;
	if (len <= 0)
		return (-1);
	data = ft_calloc(1, sizeof(t_lexer));
	if (!data)
		return (exit_failure("malloc allocation failed", 0));
	ft_memset(data, 0, sizeof(t_lexer));
	data->spaces = true;
	data->contain = ft_substr(s, start, len);
	data->lex = WORD;
	add_lexer(lexer, data);
	return (start + len);
}

static int	change_first_expand(char *contain, int i, t_lexer *lexer)
{
	int		len_exp;

	len_exp = 0;
	while (contain[len_exp + i] && !isispace(contain[len_exp + i]))
		len_exp++;
	lexer->contain = NULL;
	lexer->spaces = true;
	lexer->contain = ft_substr(contain, i, len_exp);
	i = i + len_exp;
	return (i);
}

static	void	add_env_var(t_lexer *lexer, char *contain, int start)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(contain) && contain[i])
	{
		if ((i == 0 && !isispace(contain[i]))
			|| (i > 0 && isispace(contain[i - 1]) && !isispace(contain[i])))
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
	int		start;
	t_lexer	*tmp;
	char	*contain;

	tmp = NULL;
	start = 0;
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
		contain = add_contain(lexer);
		if (contain)
			add_env_var(*lexer, contain, start);
	}
	return ((*lexer));
}
