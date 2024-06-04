/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:42:24 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/03 14:40:05 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// copy environement and add it to command list

void	cpy_env(char **env, t_cmd *command)
{
	int		len;	
	int		i;

	i = 0;
	len = 0;
	if (!command)
		return ;
	while (env[len])
		len++;
	command->t_env = malloc((len + 1) * sizeof(char *));
	while (i <= len && env[i])
	{
		command->t_env[i] = ft_strdup(env[i]);
		if (!command->t_env[i])
			exit_cmd("allocation env failed\n");// free and exit
		i++;
	}
	command->t_env[len] = NULL;
}

int	size_tab_cmd(t_lexer *lex)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	if (lex->prev && isredirection(lex->prev->lex)
		&& (!lex->prev->prev || lex->prev->prev->lex == PIPES))
		return (1);
	while (tmp  && tmp->lex != PIPES
			&& tmp->lex != INPUT && tmp->lex != OUTPUT)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

bool	isredirection(t_lexer_type lex_type)
{
	if (lex_type == INPUT
		|| lex_type == OUTPUT)
		return (true);
	return (false);
}

bool	isoperator_cmd(t_lexer_type lex_type)
{
	if (isredirection(lex_type)
		|| lex_type == PIPES)
		return (true);
	return (false);
}

bool	isbuiltin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "pwd", 4))
		return (true);
	return (false);
}