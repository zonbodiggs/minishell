/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/13 10:05:39 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// duplicate word in cmd or files.files 

char	*dup_cmd(t_lexer *lex)
{
	char	*cmd;

	if (!lex)
		return (NULL);
	if (lex->lex == SINGLE_Q || lex->lex == DOUBLE_Q 
		|| lex->lex == SINGLE_ENV || lex->lex == DOUBLE_ENV)
		cmd = ft_qstrdup(lex->contain);
	else
		cmd = ft_strdup(lex->contain);
	if (!cmd)
		exit_cmd("allocation cmd failed\n"); // free and exit
	return (cmd);
}
// put array of *cmd or *files in command

char	**init_tab(t_lexer *lex, int flag)
{
	int		len;
	int		i;
	char	**cmd;

	i = 0;
	len = size_tab_cmd(lex);
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
		exit_cmd("allocation t_cmd failed\n"); // free and exit 
	while (lex && i < len)
	{
		//if ((flag == 1 && lex->next && lex->next->lex != INPUT 
		//		&& lex->next->next && lex->next->next->lex != OUTPUT)
		//	|| (!lex->next) || (!lex->next->next) || (flag == 2))
		cmd[i] = dup_cmd(lex);
		if (lex->spaces == false)
		{
			while (lex && lex->spaces == false && !isoperator_cmd(lex->lex))
			{	
				lex = lex->next;
				if (lex && (lex->lex == SINGLE_Q || lex->lex == DOUBLE_Q 
					|| lex->lex == SINGLE_ENV || lex->lex == DOUBLE_ENV))
				{
					char *tmp = ft_qstrdup(lex->contain);
					free(lex->contain);
					lex->contain = tmp;
				}
				if (lex && lex->contain && !isoperator_cmd(lex->lex))
					cmd[i] = join_and_free(cmd[i], lex->contain);
			}
		}
		i++;
		if (lex)
			lex = lex->next;
		(void)flag;
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
		command->cmd = init_tab(lex, 1);
		lex = zap_lex(lex);
	}
	if (lex && isredirection(lex->lex) == true)
	{
		set_input(command, lex);
		if (lex->next)
		{
			if (lex->prev && lex->lex == INPUT && lex->next->lex == OUTPUT)
			{
				command->files = init_tab(lex->prev , 2);
				lex = lex->next;
			}
			else
			{
			lex = lex->next;
				command->files = init_tab(lex, 1);
				if (lex->prev->prev && lex->prev->prev->lex != PIPES)
					lex = zap_lex(lex);
			}
		}
	}
	return (lex);
}
// init struct list cmd

t_cmd	*init_cmd(char **env, t_lexer **lex)
{
	t_cmd		*command;
	t_cmd		*start;
	t_lexer		*lexer;
	int		i;

	if (!lex)
		return (NULL);
	i = 0;
	command = NULL;
	start = NULL;
	lexer = *lex;
	while (lexer)
	{
		i++;
		lst_init_cmd(env, &command);
		lexer = get_cmd(command, lexer);
		if (i == 1)
			start = command;
		if (lexer && isredirection(lexer->lex) == false)
			lexer = lexer->next;
	}
	command = start;
	free_lexer(lex);
	pars_cmd_list(command);
	return (command);
}

// test < Makefile (send Makefile in cmd)
