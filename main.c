/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/07 13:06:49 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_cmd **cmd)
{
	t_cmd		*tmpcmd;

	if (cmd)
	{
			while(*cmd && (*cmd)->next)
		{
			tmpcmd = *cmd;
			if ((*cmd)->cmd)
				free_array((*cmd)->cmd);
			if ((*cmd)->files)
				free_array((*cmd)->files);
			if ((*cmd)->t_env)
				free_array((*cmd)->t_env);
			if (*cmd && (*cmd)->next)
				*cmd = (*cmd)->next;
			free(tmpcmd);
		}
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
	(void)av;
	while(1)
	{
		minishell = ft_calloc(1, sizeof(t_minishell));
		buffer = readline("minishell> "); 					// set buffer in readline (wait for read)
		add_history(buffer);								// clear history after
		minishell->lex = create_lexer(buffer); 				// check arg in the readline 
		if (minishell->lex)
			minishell->input = init_cmd(env, minishell->lex);
		if (minishell->input)
			run_commands(minishell->input);
		free_all(&minishell->input);
		//if (!minishell->input)
		//	exit(87);
		free(minishell);
		free(buffer); // free lex and input
	}
	free(minishell);
}
