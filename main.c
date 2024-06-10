/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/10 23:33:06 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_cmd **cmd)
{
	t_cmd		*tmp;

	if (cmd)
	{
		tmp = *cmd;
		while(*cmd)
		{
			tmp = tmp->next;
			free_array((*cmd)->cmd);
			free_array((*cmd)->files);
			free_array((*cmd)->t_env);
			free(*cmd);
			*cmd = tmp;
		}
		*cmd = NULL;
		//free(cmd);
	}
}
void	kill_prompt(t_minishell *mini)
{
	free_all(&mini->input);
	mini->input = NULL;
	mini->lex = NULL;
}
int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell;

	(void)av;
	if (ac != 1)
		exit (2);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = cpy_env(env);
	while(1)
	{
		buffer = readline("minishell> "); 					// set buffer in readline (wait for read)
		if (buffer && buffer[0])
			add_history(buffer);								// clear history after
		minishell->lex = create_lexer(buffer); 				// check arg in the readline 
		if (minishell->lex)
			minishell->input = init_cmd(minishell->env, &minishell->lex);
		if (minishell->input)
			run_commands(minishell);
		free_all(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell);
}
