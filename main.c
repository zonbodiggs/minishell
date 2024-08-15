/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 23:28:16 by endoliam         ###   ########lyon.fr   */
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
t_minishell	*init_shell(t_minishell *minishell, char **env)
{
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = cpy_env(minishell, env);
	//si pas env rajout PWD fins SHLVL+=1
	return (minishell);
}
int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell = NULL;

	printf("%sWelcome to minishell an interactive 42 shell project\nhave good time :)\n\x1b[49m", "\x1b[42m");
	(void)av;	
	if (ac != 1)
	{	
		ft_printf_fd(2, "too many arguments\n");
		exit (2);
	}
	minishell = init_shell(minishell, env);
	minishell->exit_code = ft_itoa(0);
	while(1)
	{
		g_signal = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		printf("%s%s%s@%sshell rtehar+endoliam%s ~%s %s[%s%s%s]\n\x1b[0m", "\x1b[36m",mygetenv("USER",
				*minishell), "\x1b[93m", "\x1b[32m", "\x1b[95m" ,mygetenv("PWD",
				*minishell), "\x1b[93m", "\x1b[31m",
				minishell->exit_code, "\x1b[93m");
		buffer = readline("> ");
		if (!buffer)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (buffer && buffer[0])
			add_history(buffer);
		minishell->lex = create_lexer(buffer, minishell);
		//print_lexer(minishell->lex);
		if (minishell->lex)
			minishell->input = init_cmd(minishell, &minishell->lex);
		find_heredoc(minishell->input, minishell);
		//print_cmd(minishell->input);
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

// Retour erreur exit / autres btin
// here doc : CTRL+D = donne le delimiteur ^^
// droit de sortie lorsque l'on est sur un fichier sans droit