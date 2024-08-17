/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/17 03:37:43 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

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
		if (!ft_strncmp(s, mini.env[i], len) && (int)ft_strlen(s) == len)
		{
			res = ft_strchr(mini.env[i], '=') + 1;
			return (res);
		}
		i++;
	}
	return (NULL);
}

void	add_pwd(t_minishell *minishell)
{
	char	cwd[PATH_MAX];
	char	*p;
	char	**pwd;
	
	p = ft_strjoin("export,PWD=",getcwd(cwd, sizeof(cwd)));
	pwd = ft_split( p, ',');
	export_variable(pwd , &minishell->env);
	free(p);
	free_array(pwd);
}

int run_builtin(char **cmd, t_minishell *mini)
{
	if (cmd && !ft_strcmp(cmd[0], "exit"))
		exit_shell(mini, cmd);
	if (cmd && !ft_strcmp(cmd[0], "cd"))
	{
		if (!mygetenv("PWD", *mini))
			add_pwd(mini);
		return (cd(cmd, &mini->env));
	}
	if (cmd && !ft_strcmp(cmd[0], "export"))
		return (export_variable(cmd, &mini->env));
	if (cmd &&  !ft_strcmp(cmd[0], "unset"))
		return (unset_variable(cmd, &mini->env));
	return (-1);
}

int	sort_builtin(t_minishell *mini)
{
	t_cmd	*cmd;
	int		exit_code;

	cmd = mini->input;
	exit_code = 0;
	//if (!cmd->next && !cmd->cmd)
	//	return (-1);
	while (cmd)
	{
		exit_code = run_builtin(cmd->cmd, mini);
		cmd = cmd->next;
	}
	if (exit_code != -1)
		mini->exit_code = ft_itoa(exit_code);
	return (exit_code);
}

void	add_env(t_minishell *minishell)
{
	char	**shl;
	char	**path;

	shl = ft_split("export,SHLVL=1", ',');
	path = ft_split("export,PATH=/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", ',');
	if (!minishell->env || !mygetenv("PWD", *minishell))
		add_pwd(minishell);
	if (!minishell->env || !mygetenv("SHLVL", *minishell))
		export_variable(shl , &minishell->env);
	if (!minishell->env || !mygetenv("PATH", *minishell))
		export_variable(path , &minishell->env);
	free_array(shl);
	free_array(path);

}

void	update_shlvl(t_minishell *minishell)
{
	char	*lvl;
	char	*tmp;
	int		i;

	i  = 0;
	lvl = ft_itoa(ft_atoi(mygetenv("SHLVL", *minishell)) + 1);
	tmp = ft_strjoin("SHLVL=", lvl);
	if (tmp)
		set_env_var(&minishell->env, "SHLVL", tmp);
	while (ft_strncmp(minishell->env[i], "SHLVL", 5))
		i++;
	free(minishell->env[i]);
	minishell->env[i] = tmp;
	free(lvl);
}

t_minishell	*init_shell(t_minishell *minishell, char **env)
{
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (minishell->env)
		minishell->env = cpy_env(minishell, minishell->env);
	else
		minishell->env = cpy_env(minishell, env);
	add_env(minishell);
	update_shlvl(minishell);
	return (minishell);
}

void	prompt(t_minishell	*minishell)
{
	char *user;
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	user = mygetenv("USER", *minishell);
	if (!user)
		user = "ghost_user";
	printf("%s%s%s@%sshell-rtehar+endoliam:%s~%s %s[%s%s%s]\x1b[0m\x1b[02;0m\n",
				"\x1b[1;35m",user, "\x1b[93m", "\x1b[32m",
				"\x1b[95m" ,cwd, "\x1b[93m", "\x1b[31m",
				minishell->exit_code, "\x1b[93m");
}

int		main(int ac, char **av, char **env)
{
	char 		*buffer;
	t_minishell *minishell = NULL;

	(void)av;	
	if (ac != 1)
	{	
		ft_printf_fd(2, "too many arguments\n");
		exit (2);
	}
	printf("%sWelcome to minishell an interactive 42 shell project\x1b[49m\n", "\x1b[40m");
	printf("%shave good time :) !\x1b[49m\n", "\x1b[40m");
	minishell = init_shell(minishell, env);
	minishell->exit_code = ft_itoa(0);
	while(1)
	{
		g_signal = 0;
		set_input_signal();
		prompt(minishell);
		buffer = readline("~ ");
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
			if (sort_builtin(minishell) == -1)
				minishell->exit_code = run_commands(minishell);
		}
		if (g_signal == 130)
		{
			free(minishell->exit_code);	
			minishell->exit_code = ft_itoa(130);
		}
		free_input(&minishell->input);
		free(minishell->input);
	}
	rl_clear_history();
	free(minishell->exit_code);
	free_array(minishell->env);
	free(minishell);
}

// here doc : CTRL+D = donne le delimiteur ^^
// droit de sortie lorsque l'on est sur un fichier sans droit