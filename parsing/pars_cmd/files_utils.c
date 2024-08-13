/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:42:36 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 01:33:01 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// set enum redirection of command

void	set_input(t_cmd *command, t_lexer *lex)
{
	if (lex->lex == INPUT)
	{
		if (ft_strlen(lex->contain) == 2)
			command->redir = HEREDOC;
		else
			command->redir = IN;
	}
	else if (lex->lex == OUTPUT)
	{
		if ((ft_strlen(lex->contain) == 2))
			command->redir = APPEND;
		else if (ft_strlen(lex->contain) == 1)
			command->redir = TRUNC;
	}
}

char	*init_files(t_lexer *lex)
{
	char	*file;

	file = ft_strdup(lex->contain);
	if (lex->spaces == false)
	{
		file = join_cmd(lex, file);
		while (lex && !lex->spaces && !isoperator_cmd(lex->lex))
			lex = lex->next;
	}
	return (file);
}

int	isfilevalid_in(char *file)
{
	if (access(file, F_OK) == -1)
		return (2);
	if (access(file, R_OK) == -1)
		return (1);
	return (0);
}

int	isfilevalid_out(char *file)
{
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (2);
	return (0);
}
