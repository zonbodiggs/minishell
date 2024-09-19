/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:42:36 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/18 14:33:17 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*init_files(t_cmd *command, t_lexer *lex, t_minishell *mini)
{
	char	*file;

	if (lex->lex == SINGLE_Q || lex->lex == DOUBLE_Q
		|| lex->lex == SINGLE_ENV || lex->lex == DOUBLE_ENV)
		file = ft_qstrdup(lex->contain);
	else
		file = ft_strdup(lex->contain);
	if (lex->spaces == false)
	{
		file = join_cmd(lex, file);
		while (lex && !lex->spaces && !isoperator_cmd(lex->lex))
			lex = lex->next;
	}
	if (!file)
	{
		free_all_input(command);
		exit_cmd("allocation file failed\n", mini, 2);
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

int	can_access_dir(char *file)
{
	int		i;
	char	*tmp;
	int		res;

	tmp = ft_strdup(file);
	i = ft_strlen(file);
	while (i >= 0 && file[i] != '/')
		i--;
	res = 0;
	tmp[i] = '\0';
	if (is_directory(tmp) == false)
		res = 2;
	else if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		res = 1;
	free (tmp);
	return (res);
}

int	isfilevalid_out(char *file)
{
	if (ft_strchr(file, '/'))
		return (can_access_dir(file));
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (2);
	return (0);
}
