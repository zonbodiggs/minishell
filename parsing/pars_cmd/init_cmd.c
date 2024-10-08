/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/19 11:01:07 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*zap_redirect_token(t_lexer *lex, t_cmd *command)
{
	if (command->cmd)
	{
		while (lex && !isoperator_cmd(lex->lex))
			lex = lex->next;
	}
	else
	{
		while (lex && !lex->spaces && !isoperator_cmd(lex->lex))
			lex = lex->next;
	}
	if (lex && lex->next && !isoperator_cmd(lex->lex))
		lex = lex->next;
	if ((lex && lex->lex == SINGLE_Q)
		|| (lex && lex->lex == DOUBLE_Q))
		lex = lex->next;
	return (lex);
}

t_lexer	*get_cmd(t_cmd *command, t_lexer *lex, t_minishell *mini)
{
	if (lex && !isoperator_cmd(lex->lex))
	{
		command->cmd = init_tab(command, lex, mini);
		while (lex && !isoperator_cmd(lex->lex))
			lex = lex->next;
	}
	if (lex && isredirection(lex->lex) == true)
	{
		set_input(command, lex);
		if (lex->next)
		{
			lex = lex->next;
			command->files = init_files(command, lex, mini);
			lex = zap_redirect_token(lex, command);
		}
	}
	if (lex && lex->lex == PIPES)
		command->pipe = true;
	return (lex);
}

t_cmd	*init_cmd(t_minishell *mini, t_lexer **lex)
{
	t_cmd		*command;
	t_cmd		*start;
	t_lexer		*lexer;
	int			i;

	if (!lex)
		return (NULL);
	i = 0;
	command = NULL;
	lexer = *lex;
	while (lexer)
	{
		i++;
		if (lexer && lexer->lex == PIPES)
			lexer = lexer->next;
		lst_init_cmd(mini, &command);
		lexer = get_cmd(command, lexer, mini);
		if (isthereredirection(lexer, command))
			lexer = lexer->next;
		if (i == 1)
			start = command;
	}
	command = start;
	free_lexer(lex);
	return (command);
}
