/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/16 12:34:09 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_pipe(t_minishell *mini)
{
	bool	free;
	t_cmd	*tmp;
	int		exit;
	int		value;

	free = true;
	value = 0;
	while (mini->input && !mini->input->pipe)
	{
		tmp = mini->input->next;
		if (mini->input->cmd)
			free = false;
		exit = redirect(mini);
		if (free)
			free_one_input(mini->input);
		mini->input = tmp;
		if (exit != 0)
			value = exit;
	}
	if (mini->input && mini->input->pipe)
		exit = redirect(mini);
	if (exit != 0)
		value = exit;
	return (value);
}

int	prepare_execution(t_minishell *mini, t_cmd	*cmd)
{
	int		value;
	int		value_redir;

	value = 0;
	value_redir = 0;
	if (cmd)
		value = iscmd(cmd->cmd, mini);
	value_redir = redirect_pipe(mini);
	if (value_redir != 0)
		value = value_redir;
	return (value);
}

int	my_execve(t_minishell *mini)
{
	t_cmd	*cmd;
	int		value;

	cmd = get_pipe_comd(mini->input);
	value = prepare_execution(mini, cmd);
	mini->input = cmd;
	if (value == 0 && cmd && cmd->cmd && isbuiltin(cmd->cmd[0]) == true)
		exec_builtin(mini, cmd);
	if (value != 0 || !cmd || !cmd->cmd
		|| (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1))
		return (exit_error_exec(mini, value));
	return (value);
}

char	*run_commands(t_minishell *mini)
{
	int		i;
	int		exit_code;

	exit_code = 0;
	if (!mini->input)
		return (0);
	i = number_of_command(mini->input);
	if (!mini->input->next || i == 0)
		exit_code = execute_simple_command(mini);
	else
		exit_code = execute_pipeline(mini);
	return (ft_itoa(exit_code));
}
