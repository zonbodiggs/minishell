/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/20 17:59:25 by endoliam         ###   ########lyon.fr   */
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

int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell;
	
	if (ac != 1)
	{	
		ft_printf_fd(2, "too many arguments");
		exit (2);
	}
	(void)av;
	//signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = cpy_env(env);
	while(1)
	{
		buffer = readline("minishell> ");
		if (buffer == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (buffer && buffer[0])
			add_history(buffer);
		minishell->lex = create_lexer(buffer);
		print_lexer(minishell->lex);
		if (minishell->lex)
			minishell->input = init_cmd(minishell->env, &minishell->lex);
		print_cmd(minishell->input);
		if (minishell->input)
		{
			if (minishell->input->cmd && ft_strncmp(minishell->input->cmd[0], "exit", 4) == 0)
				exit_shell(minishell, minishell->input->cmd);
			run_commands(minishell);
		}
		free_all(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell);
}

// mise en place heredoc
// expand (when expand lex have multiple $)
// help export
// signals
// <Make'file' cat (fon't work correctly)
// return value 