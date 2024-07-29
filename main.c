/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/24 16:11:44 by endoliam         ###   ########lyon.fr   */
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

void run_builtin(char *cmd, t_minishell *mini)
{
	if (cmd && ft_strlen(cmd) == 4 && ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		exit_shell(mini, mini->input->cmd);
	if (!mini->input->cmd[1])
	{
		if (cmd && ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
			export_variable(mini->input->cmd, &mini->env);
		else if (cmd && ft_strlen(cmd) == 5 && ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
			unset_variable(mini->input->cmd, &mini->env);
		else if (cmd && ft_strlen(cmd) == 2 && ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
			cd(mini->input->cmd, &mini->env);
	}	
}

void	sort_builtin(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = mini->input;
	while (cmd && cmd->cmd)
	{
		run_builtin(cmd->cmd[0], mini);
		cmd = cmd->next;
	}
	return ;
}

int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell;

	(void)av;	
	if (ac != 1)
	{	
		ft_printf_fd(2, "too many arguments\n");
		exit (2);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = cpy_env(env);
	while(1)
	{
		buffer = readline("minishell> ");
		if (!buffer)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (buffer && buffer[0])
			add_history(buffer);
		minishell->lex = create_lexer(buffer, minishell);
		print_lexer(minishell->lex);
		if (minishell->lex)
			minishell->input = init_cmd(minishell->env, &minishell->lex);
		print_cmd(minishell->input);
		if (minishell->input)
		{
			sort_builtin(minishell);
			run_commands(minishell);
		}
		free_all(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell);
}

// mise en place heredoc
// return value
// gestion ispace
// gestion backslash