/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 16:17:46 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**init_tab(t_cmd *command, t_lexer *lex, t_minishell *mini)
{
	int		len;
	int		i;
	char	**cmd;

	i = 0;
	len = size_tab_cmd(lex);
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
	{	
		free_all_input(command);
		exit_cmd("allocation t_cmd failed\n", mini, 2);
	}
	while (lex && i < len)
	{
		cmd[i] = dup_cmd(lex, mini);
		if (lex->spaces == false)
		{
			cmd[i] = join_cmd(lex, cmd[i], mini, command);
			if (!cmd[i])
			{
				free(cmd);
				free_all_input(command);
				exit_cmd("allocation t_cmd failed\n", mini, 2);
			}
			while (lex && !lex->spaces && !isoperator_cmd(lex->lex))
				lex = lex->next;
		}
		lex = go_next_cmd(lex);
		i++;
	}
	return (cmd);
}

t_lexer	*get_cmd(t_cmd *command, t_lexer *lex, t_minishell *mini)
{
	if (lex && !isoperator_cmd(lex->lex))
	{
		command->cmd = init_tab(command, lex, mini);
		while (lex && isoperator_cmd(lex->lex) == false)
			lex = lex->next;
	}
	if (lex && isredirection(lex->lex) == true)
	{
		set_input(command, lex);
		if (lex->next)
		{
			lex = lex->next;
			command->files = init_files(command, lex, mini);
			while (lex && !lex->spaces && !isoperator_cmd(lex->lex))
				lex = lex->next;
			if (lex && lex->next && !isoperator_cmd(lex->lex))
				lex = lex->next;
			if ((lex && lex->lex == SINGLE_Q)
				|| (lex && lex->lex == DOUBLE_Q))
				lex = lex->next;
		}
	}
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
		if (lexer && lexer->lex == PIPES)
			command->pipe = true;
		if (i == 1)
			start = command;
		if (isthereredirection(lexer, command))
			lexer = lexer->next;
	}
	command = start;
	free_lexer(lex);
	return (command);
}
