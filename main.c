/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/11 14:12:48 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

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
int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell;
	
	if (ac != 1)
		exit (2);
	(void)av;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = cpy_env(env);
	while(1)
	{
		buffer = readline("minishell> "); 					// set buffer in readline (wait for read)
		if (buffer == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (buffer && buffer[0])
			add_history(buffer);								// clear history after
		minishell->lex = create_lexer(buffer); 				// check arg in the readline 
		if (minishell->lex)
			minishell->input = init_cmd(minishell->env, &minishell->lex);
		if (minishell->input)
		{
			if (ft_strncmp(minishell->input->cmd[0], "exit", 4) == 0)
			{
				exit_shell(minishell, minishell->input->cmd);
				free(buffer);
				free(minishell);
				exit(1);
			} //pas sur du free et de l'endroit mdr
			run_commands(minishell);
		}
		free_all(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell);
}
