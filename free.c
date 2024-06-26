/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:35:04 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/12 13:05:50 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_shell(t_minishell *shell)
{
	free_all(&shell->input);
	free(shell->input);
	free_array(shell->env);
	ft_memset(shell, 0, sizeof(shell));
	free(shell);
	rl_clear_history();
}

void	free_all(t_cmd **cmd)
{
	t_cmd		*tmp;

	if (cmd)
	{
		tmp = *cmd;
		while(*cmd)
		{
			tmp = tmp->next;
			free_cmd(cmd);
			free(*cmd);
			*cmd = tmp;
		}
		*cmd = NULL;
	}
}

t_lexer		*free_lexer(t_lexer **lex)
{
	t_lexer	*tmp;

	if (!lex)
		return (NULL);
	tmp = *lex;
	while(*lex)
	{
		tmp = tmp->next;
		free((*lex)->contain);
		(*lex)->contain = NULL;
		free(*lex);
		*lex = tmp;
	}
	*lex = 0;
	return (NULL);
}

void	free_cmd(t_cmd **cmd)
{
	if (!cmd || !(*cmd))
		return ;
	if ((*cmd)->cmd)
		free_array((*cmd)->cmd);
	if ((*cmd)->files)
		free_array((*cmd)->files);
	if ((*cmd)->t_env)
		free_array((*cmd)->t_env);
}
