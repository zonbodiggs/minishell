/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:43:05 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/15 16:31:32 by endoliam         ###   ########lyon.fr   */
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
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (echo(cmd));
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (pwd());
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (env_shell(env));
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		return (export_variable(cmd, &env));
	return (127);
}
