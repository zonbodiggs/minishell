/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/22 17:16:46 by endoliam         ###   ########lyon.fr   */
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
char	*mygetenv(char *s, char **env)
{
	int		i;
	int		len;
	char	*res;

	len = 0;
	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		len = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		if (!ft_strncmp(s, env[i], len))
		{
			res = ft_strchr(env[i], '=') + 1;
			return (res);
		}
		i++;
	}
	return (NULL);
}
void sort_env(char **cmd, char ***env)
{
	if (cmd && ft_strncmp(cmd[0], "export", 6) == 0)
		export_variable(cmd, env);
	else if (cmd && ft_strncmp(cmd[0], "unset", 5) == 0)
		unset_variable(cmd, env);
	else if (cmd && ft_strncmp(cmd[0], "cd", 2) == 0)
		cd(cmd, env);
	return ;
}

int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell;
	
	if (ac != 1)
	{	
		ft_printf_fd(2, "too many arguments\n");
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
		minishell->lex = create_lexer(buffer, *minishell);
		if (minishell->lex)
			minishell->input = init_cmd(minishell->env, &minishell->lex);
		if (minishell->input)
		{
			if (minishell->input->cmd && ft_strncmp(minishell->input->cmd[0], "exit", 4) == 0)
				exit_shell(minishell, minishell->input->cmd);
			sort_env(minishell->input->cmd, &minishell->env);
			run_commands(minishell);
		}
		free_all(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell);
}

// mise en place heredoc
// help export
// signals
// return value
// gestion ispace
// gestion backslash
// finir mise en place export unset et exit