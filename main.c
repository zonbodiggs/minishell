/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/05 16:02:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_all(t_lexer *lex, t_cmd *cmd)
{
	t_lexer		*tmplex;
	t_cmd		*tmpcmd;
	while(lex)
	{
		tmplex = lex;
		free(tmplex->contain);
		lex = lex->next;
		free(tmplex);
		
	}
	while(cmd)
	{
		tmpcmd = cmd;
		if (cmd->cmd)
			free_array(cmd->cmd);
		if (cmd->files)
			free_array(cmd->files);
		cmd = cmd->next;
		free(tmpcmd);
	}
}
int		main(int ac, char **av, char **env)
{
	char *buffer;
	t_minishell *minishell;

	if (!*env || ac != 1 || !getenv("PATH"))
	{
		ft_putstr_fd("could not execute minishell\n", 2);
		return (0);
	}
	minishell = ft_calloc(1, sizeof(t_minishell));
	(void)av;
	while(1)
	{
		buffer = readline("minishell> "); 					// set buffer in readline (wait for read)
		add_history(buffer);								// clear history after
		minishell->lex = create_lexer(buffer); 				// check arg in the readline 
		minishell->input = init_cmd(env, minishell->lex);
		if (minishell->input)
			run_commands(minishell->input);
		free_all(minishell->lex, minishell->input);
		free(buffer); // free lex and input
	}
	free(minishell);
}
