/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:57:36 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/19 10:56:03 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmd_malloc(char **s, t_cmd *cmd, t_minishell *mini, int i)
{
	if (i >= 0 && !s[i])
	{
		free(s);
		free_all_input(cmd);
		exit_cmd("allocation t_cmd failed\n", mini, 2);
	}
	if (!s)
	{
		free_all_input(cmd);
		exit_cmd("allocation t_cmd failed\n", mini, 2);
	}
}

char	**init_tab(t_cmd *command, t_lexer *lex, t_minishell *mini)
{
	int		len;
	int		i;
	char	**cmd;

	i = 0;
	len = size_tab_cmd(lex);
	if (len == 0)
		return (NULL);
	cmd = ft_calloc(len + 1, sizeof(char *));
	free_cmd_malloc(cmd, command, mini, -6);
	while (lex && i < len)
	{
		if (lex && lex->lex && !isoperator_cmd(lex->lex))
			cmd[i] = dup_cmd(lex, mini);
		if (lex && !lex->spaces && lex->lex && !isoperator_cmd(lex->lex))
		{
			cmd[i] = join_cmd(lex, cmd[i]);
			free_cmd_malloc(cmd, command, mini, i);
			while (lex && !lex->spaces && !isoperator_cmd(lex->lex))
				lex = lex->next;
		}
		lex = go_next_cmd(lex);
		i++;
	}
	return (cmd);
}
