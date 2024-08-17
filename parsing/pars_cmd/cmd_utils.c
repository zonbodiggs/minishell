/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:42:24 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/16 21:12:26 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*zap_redirection(t_lexer *lex)
{
	while ((lex && lex->prev && isredirection(lex->prev->lex))
		|| (lex && isredirection(lex->lex)))
		lex = lex->next;
	return (lex);
}

t_lexer	*go_next_cmd(t_lexer *lex)
{
	if (lex)
		lex = lex->next;
	if (lex && lex->lex && isredirection(lex->lex))
		lex = zap_redirection(lex);
	return (lex);
}

int	size_tab_cmd(t_lexer *lex)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	if (lex->prev && isredirection(lex->prev->lex))
		return (1);
	while (tmp && tmp->lex != PIPES)
	{
		i++;
		if (tmp->spaces == false && !isredirection(tmp->lex))
		{
			while (tmp && isoperator_cmd(tmp->lex) == false
				&& tmp->spaces == false)
				tmp = tmp->next;
		}
		if (tmp && isoperator_cmd(tmp->lex) == false)
			tmp = tmp->next;
		if (tmp && tmp->lex && isredirection(tmp->lex))
			tmp = zap_redirection(tmp);
	}
	return (i);
}

char	*join_cmd(t_lexer *lex, char *cmd, t_minishell *mini, t_cmd *command)
{
	char	*tmp;

	tmp = NULL;
	while (lex && lex->spaces == false && !isoperator_cmd(lex->lex))
	{
		lex = lex->next;
		if (lex && !isredirection(lex->lex) && (lex->lex == SINGLE_Q
				|| lex->lex == DOUBLE_Q || lex->lex == SINGLE_ENV))
		{
			tmp = ft_qstrdup(lex->contain);
			if (!tmp)
			{
				free(cmd);
				free_all_input(command);
				exit_cmd("allocation join failed\n", mini, 2);
			}
			free(lex->contain);
			lex->contain = tmp;
		}
		if (lex && lex->contain && !isoperator_cmd(lex->lex))
		{
			tmp = join_and_free(cmd, lex->contain);
			if (!tmp)
			{
				free(cmd);
				return (NULL);
			}
			else
				cmd = tmp;
		}
	}
	return (cmd);
}

char	*dup_cmd(t_lexer *lex, t_minishell *mini)
{
	char	*cmd;

	if (!lex)
		return (NULL);
	if (lex->lex == SINGLE_Q || lex->lex == DOUBLE_Q
		|| lex->lex == SINGLE_ENV)
		cmd = ft_qstrdup(lex->contain);
	else
		cmd = ft_strdup(lex->contain);
	if (!cmd)
		exit_cmd("allocation cmd failed\n", mini, 2);
	return (cmd);
}
