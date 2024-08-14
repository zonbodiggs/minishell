/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 18:59:45 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}

void	handle_sigquit(int sig)
{
	(void)sig;
}
char	*mygetenv(char *s, t_minishell mini)
{
	int		i;
	int		len;
	char	*res;

	len = 0;
	i = 0;
	if (!ft_strncmp(s, "?", ft_strlen(s)))
		return (mini.exit_code);
	if (!mini.env)
		return (NULL);
	while (mini.env[i])
	{
		len = ft_strlen(mini.env[i]) - ft_strlen(ft_strchr(mini.env[i], '='));
		if (!ft_strncmp(s, mini.env[i], len))
		{
			res = ft_strchr(mini.env[i], '=') + 1;
			return (res);
		}
		i++;
	}
	return (NULL);
}

void run_builtin(char **cmd, t_minishell *mini)
{
	if (cmd && ft_strlen(cmd[0]) == 4 && ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
		exit_shell(mini, cmd);
	if (cmd && ft_strlen(cmd[0]) == 2 && ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
			cd(cmd, &mini->env);
	if (cmd && ft_strlen(cmd[0]) == 6 && ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
		export_variable(cmd, &mini->env);
	if (cmd && ft_strlen(cmd[0]) == 5 && ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		unset_variable(cmd, &mini->env);
}

void	sort_builtin(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = mini->input;
	while (cmd && cmd->cmd)
	{
		run_builtin(cmd->cmd, mini);
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
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = cpy_env(minishell, env);
	//si pas env rajout PWD fins SHLVL+=1
	while(1)
	{
		g_signal = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline("minishell> ");
		if (!buffer)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (buffer && buffer[0])
			add_history(buffer);
		minishell->lex = create_lexer(buffer, minishell);
		// print_lexer(minishell->lex);
		if (minishell->lex)
			minishell->input = init_cmd(minishell, &minishell->lex);
		find_heredoc(minishell->input, minishell);
		print_cmd(minishell->input);
		if (minishell->input)
		{
			free(minishell->exit_code);
			sort_builtin(minishell);
			minishell->exit_code = run_commands(minishell);
		}
		free_input(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell->exit_code);
	free_array(minishell->env);
	free(minishell);
}

// gestion backslash a voir
// "" = pas permission denied mais cmd not fount
// Leak avec cmd | ""
// cat < | hey prend | pour un infile
// PWD chelou sans = apres des CD, oldpwd a pas de =
// Code erreur de /bla/bin = 2 au lieu de 127
// ./directory -> Is a directory, code 126 
// Prendre le statut d'exit seulement du dernier enfant cree
// echo << bye << bla | cat heredoc no such file ?
// Retour erreur exit / autres btin