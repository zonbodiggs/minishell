/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:54:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 23:18:38 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	number_of_command(t_cmd *cmd)
{
	int		i;
	t_cmd	*start;

	if (!cmd)
		return (0);
	i = 0;
	start = cmd;
	while (start)
	{
		if (start && start->pipe)
			i++;
		start = start->next;
	}
	return (i);
}

bool	is_last_cmd(t_cmd	*cmd)
{
	if (!cmd->next)
		return (true);
	while (cmd)
	{
		if (cmd && cmd->pipe)
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

t_cmd	*get_pipe_comd(t_cmd *cmd)
{
	while (cmd && !cmd->cmd && !cmd->pipe)
	{
		if (cmd->cmd)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

void	init_fds(int oldfd[2], int newfd[2])
{
	ft_memset(oldfd, -1, 2 * sizeof(int));
	ft_memset(newfd, -1, 2 * sizeof(int));
}
