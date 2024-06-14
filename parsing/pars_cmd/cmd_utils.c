/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:42:24 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/12 19:23:54 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	size_tab_cmd(t_lexer *lex)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lex;
	if (lex->prev && isredirection(lex->prev->lex)
		&& (!lex->prev->prev || lex->prev->prev->lex == PIPES))
		return (1);
	while (tmp  && !isoperator_cmd(tmp->lex))
	{
		i++;
		if (tmp->spaces == false)
		{
			while (tmp && isoperator_cmd(tmp->lex) == false 
				&& tmp->spaces == false)
				tmp = tmp->next;
		}
		if (tmp && isoperator_cmd(tmp->lex) == false)
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
	if (!cmd || !cmd[0])
		return (false);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "cd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "export", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd)) 
		|| !ft_strncmp(cmd, "env", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (true);
	return (false);
}