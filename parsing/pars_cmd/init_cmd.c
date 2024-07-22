/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/18 18:12:18 by endoliam         ###   ########lyon.fr   */
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
		exit_cmd("allocation cmd failed\n");
	return (cmd);
}

t_lexer	*zap_redirection(t_lexer *lex)
{
	while ((lex && lex->prev && isredirection(lex->prev->lex))
		|| (lex && isredirection(lex->lex)))
		lex = lex->next;
	return (lex);
}
// put array of *cmd or *files in command

char	**init_tab(t_lexer *lex)
{
	int		len;
	int		i;
	char	**cmd;
	char	*tmp;

	i = 0;
	len = size_tab_cmd(lex);
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
		exit_cmd("allocation t_cmd failed\n");
	tmp = NULL;
	while (lex && i < len)
	{
		cmd[i] = dup_cmd(lex);
		if (lex->spaces == false)
		{
			while (lex && lex->spaces == false && !isoperator_cmd(lex->lex))
			{
				lex = lex->next;
				if (lex && !isredirection(lex->lex) && (lex->lex == SINGLE_Q
						|| lex->lex == DOUBLE_Q || lex->lex == SINGLE_ENV
						|| lex->lex == DOUBLE_ENV))
				{
					tmp = ft_qstrdup(lex->contain);
					free(lex->contain);
					lex->contain = tmp;
				}
				if (lex && lex->contain && !isoperator_cmd(lex->lex))
					cmd[i] = join_and_free(cmd[i], lex->contain);
			}
		}
		if (lex)
			lex = lex->next;
		if (lex && lex->lex && isredirection(lex->lex))
			lex = zap_redirection(lex);
		i++;
	}
	return (cmd);
}

int	size_files(t_lexer *lex)
{
	int		i;
	t_lexer	*tmp;

	tmp = lex;
	i = 0;
	while ((tmp && isredirection(tmp->lex))
		|| (tmp && tmp->prev && isredirection(tmp->prev->lex)))
	{
		if (tmp && !isredirection(tmp->lex))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**init_files(t_lexer *lex)
{
	int		len;
	int		i;
	char	**cmd;
	char	*tmp;

	tmp = NULL;
	i = 0;
	len = size_files(lex);
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
		exit_cmd("allocation t_cmd failed\n");
	while (lex && i < len)
	{
		lex = lex->next;
		cmd[i] = dup_cmd(lex);
		if (lex->spaces == false && lex->next && !isredirection(lex->next->lex))
		{
			while (lex && lex->spaces == false && !isoperator_cmd(lex->lex))
			{
				lex = lex->next;
				if (lex && !isredirection(lex->lex) && (lex->lex == SINGLE_Q
						|| lex->lex == DOUBLE_Q || lex->lex == SINGLE_ENV
						|| lex->lex == DOUBLE_ENV))
				{
					tmp = ft_qstrdup(lex->contain);
					free(lex->contain);
					lex->contain = tmp;
				}
				if (lex && lex->contain && !isoperator_cmd(lex->lex))
					cmd[i] = join_and_free(cmd[i], lex->contain);
			}
		}
		if (lex)
			lex = lex->next;
		i++;
	}
	return (cmd);
}

t_lexer	*zap_lex(t_lexer *lex)
{
	while (lex && isoperator_cmd(lex->lex) == false)
		lex = lex->next;
	return (lex);
}

t_lexer	*get_cmd(t_cmd *command, t_lexer *lex)
{
	if (lex && isoperator_cmd(lex->lex) == false)
	{
		command->cmd = init_tab(lex);
		lex = zap_lex(lex);
	}
	if (lex && isredirection(lex->lex) == true)
	{
		set_input(command, lex);
		if (lex->next)
		{
			command->files = init_files(lex);
			lex = zap_redirection(lex);
			if ((lex && lex->lex == SINGLE_Q)
				|| (lex && lex->lex == DOUBLE_Q))
				lex = lex->next;
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
	int			i;

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
		if ((lexer && isredirection(lexer->lex) == false)
			&& (command && command->redir != IN))
			lexer = lexer->next;
	}
	command = start;
	free_lexer(lex);
	pars_cmd_list(command);
	return (command);
}

// test < Makefile (send Makefile in cmd)
