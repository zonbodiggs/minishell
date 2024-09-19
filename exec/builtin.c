/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:43:05 by rtehar            #+#    #+#             */
/*   Updated: 2024/09/19 10:38:19 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_minishell *mini, t_cmd *cmd)
{
	int	exit_code;

	exit_code = sort_cmd(cmd->cmd, mini->env);
	kill_shell(mini);
	exit(exit_code);
}

int	sort_cmd(char **cmd, char **env)
{
	if (ft_strcmp(cmd[0], "echo") == 0 && ft_strlen(cmd[0]) == 4)
		return (echo(cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0 && ft_strlen(cmd[0]) == 3)
		return (pwd(cmd));
	else if (ft_strcmp(cmd[0], "env") == 0 && ft_strlen(cmd[0]) == 3)
		return (env_shell(env, cmd));
	return (1);
}

int	run_builtin(char **cmd, t_minishell *mini)
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
	if (cmd && !ft_strcmp(cmd[0], "unset"))
		return (unset_variable(cmd, &mini->env));
	return (-1);
}

int	sort_builtin(t_minishell *mini)
{
	t_cmd	*cmd;
	int		exit_code;

	cmd = mini->input;
	exit_code = -1;
	if (number_of_command(mini->input) == 0)
		exit_code = run_builtin(cmd->cmd, mini);
	if (exit_code != -1)
		mini->exit_code = ft_itoa(exit_code);
	return (exit_code);
}
