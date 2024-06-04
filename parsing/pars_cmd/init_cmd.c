/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/03 14:13:17 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// duplicate word in cmd or files.files 

char	*dup_cmd(t_lexer *lex)
{
	char	*cmd;

	if (!lex)
		return (NULL);
	if (lex->lex == SINGLE_Q || lex->lex == DOUBLE_Q)
		cmd = ft_qstrdup(lex->contain);
	else
		cmd = ft_strdup(lex->contain);
	if (!cmd)
		exit_cmd("allocation cmd failed\n"); // free and exit
	return (cmd);
}
// put array of *cmd or *files in command

char	**init_tab(t_lexer *lex)
{
	int		len;
	int		i;
	char	**cmd;

	i = 0;
	len = size_tab_cmd(lex);
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
		exit_cmd("allocation t_cmd failed\n"); // free and exit 
	while (i < len)
	{
		cmd[i] = dup_cmd(lex);
		i++;
		lex = lex->next;
	}
	return (cmd);
}
t_lexer		*zap_lex(t_lexer *lex)
{	
	while (lex && isoperator_cmd(lex->lex) == false)
				lex = lex->next;
	return (lex);
}

t_lexer		*get_cmd(t_cmd *command, t_lexer *lex)
{
	if (lex && isoperator_cmd(lex->lex) == false)
	{
		command->cmd = init_tab(lex);
		lex = zap_lex(lex);
	}
	if (lex && isredirection(lex->lex) == true)
	{
		set_input(command, lex);
		if (lex->next && isoperator_cmd(lex->next->lex) == false)
		{
			lex = lex->next;
			command->files = init_tab(lex);
			if (lex->prev->prev && lex->prev->prev->lex != PIPES)
				lex = zap_lex(lex);
		}
		else
		{
			ft_printf_fd(2, "syntax error near unexpected token '%s'\n", lex->contain); 
			return (NULL); // free and exit correctly
		}
	}
	return (lex);
}
// init struct list cmd

t_cmd	*init_cmd(char **env, t_lexer *lex)
{
	t_cmd	*command;
	t_cmd	*start;
	int		i;

	if (!lex)
		return (NULL);
	i = 0;
	command = NULL;
	start = NULL;
	while (lex)
	{
		i++;
		lst_init_cmd(env, &command);
		lex = get_cmd(command, lex);
		if (i == 1)
			start = command;
		if (lex && isredirection(lex->lex) == false)
			lex = lex->next;
	}
	command = start;
	// hererdoc 
	pars_cmd_list(command);
	return (command);
}

// test < Makefile (send Makefile in cmd)
