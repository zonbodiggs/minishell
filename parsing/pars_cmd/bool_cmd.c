/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:53:22 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/24 19:09:01 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
bool	isthereredirection(t_lexer *lexer, t_cmd *command)
{
	if ((lexer && !isredirection(lexer->lex))
		&& (command && command->redir != IN)
		&& (command && command->redir != TRUNC)
		&& (command && command->redir != APPEND)
		&& (command && command->redir != HEREDOC))
			return (true);
	return (false);
}