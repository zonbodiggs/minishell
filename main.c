/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/19 15:33:02 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static t_minishell	*init_shell(t_minishell *minishell, char **env)
{
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (minishell->env)
		minishell->env = cpy_env(minishell, minishell->env);
	else
		minishell->env = cpy_env(minishell, env);
	add_env(minishell);
	update_shlvl(minishell);
	minishell->exit_code = ft_itoa(0);
	return (minishell);
}

static void	prompt(t_minishell	*minishell)
{
	char	*user;
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		pwd = "lost_path";
	else
		pwd = cwd;
	user = mygetenv("USER", *minishell);
	if (!user)
		user = "ghost_user";
	printf("%s%s%s@%sshell-rtehar+endoliam:%s~%s %s[%s%s%s]\x1b[0m\x1b[02;0m\n",
		"\x1b[1;35m", user, "\x1b[93m", "\x1b[32m",
		"\x1b[95m", pwd, "\x1b[93m", "\x1b[31m",
		minishell->exit_code, "\x1b[93m");
}

static void	run_minishell(t_minishell *minishell, char *buffer)
{
	if (buffer && buffer[0])
		add_history(buffer);
	minishell->lex = create_lexer(buffer, minishell);
	free(buffer);
	if (minishell->lex)
		minishell->input = init_cmd(minishell, &minishell->lex);
	find_heredoc(minishell->input, minishell);
	if (minishell->input)
	{
		free(minishell->exit_code);
		if (sort_builtin(minishell) == -1)
			minishell->exit_code = run_commands(minishell);
	}
	if (g_signal != 0)
	{
		free(minishell->exit_code);
		minishell->exit_code = ft_itoa(g_signal);
	}
	if (minishell->input)
	{
		free_input(&minishell->input);
		free(minishell->input);
	}
}

static void	start_shell(int ac)
{
	if (ac != 1)
	{
		ft_printf_fd(2, "minishell : too many arguments\n");
		exit (2);
	}
	printf("%sWelcome to minishell an interactive 42 shell project\x1b[49m\n",
		"\x1b[40m");
	printf("%shave good time :) !\x1b[49m\n", "\x1b[40m");
}

int	main(int ac, char **av, char **env)
{
	char			*buffer;
	t_minishell		*minishell;

	(void)av;
	minishell = NULL;
	start_shell(ac);
	(void )ac;
	minishell = init_shell(minishell, env);
	while (1)
	{
		g_signal = 0;
		set_input_signal();
		prompt(minishell);
		buffer = readline("~ ");
		if (!buffer)
		{
			write(1, "exit\n", 5);
			break ;
		}
		run_minishell(minishell, buffer);
	}
	rl_clear_history();
	free(minishell->exit_code);
	free_array(minishell->env);
	free(minishell);
}
