/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:35:04 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 21:03:27 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer **lex)
{
	t_lexer	*tmp;

	if (!lex)
		return ;
	if (*lex &&(*lex)->prev)
	{
		while ((*lex)->prev)
			*lex = (*lex)->prev;
	}
	tmp = *lex;
	while (*lex)
	{
		tmp = tmp->next;
		free((*lex)->contain);
		(*lex)->contain = NULL;
		free(*lex);
		*lex = tmp;
	}
	*lex = 0;
}

void	free_input(t_cmd **cmd)
{
	t_cmd		*tmp;

	if (cmd)
	{
		tmp = *cmd;
		while (*cmd)
		{
			tmp = tmp->next;
			free_one_input(*cmd);
			*cmd = tmp;
		}
		*cmd = NULL;
	}
}

void	free_cmd(t_cmd **cmd)
{
	if (!cmd || !(*cmd))
		return ;
	if ((*cmd)->cmd)
		free_array((*cmd)->cmd);
	if ((*cmd)->files)
		free((*cmd)->files);
	if ((*cmd)->t_env)
		free_array((*cmd)->t_env);
}

void	free_one_input(t_cmd *cmd)
{
	free_cmd(&cmd);
	free(cmd);
	cmd = NULL;
}

void	free_all_input(t_cmd *cmd)
{
	free_input(&cmd);
	free(cmd);
}
