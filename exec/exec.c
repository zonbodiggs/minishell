/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/04 17:22:42 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_execve(t_cmd *cmd)
{
	if (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
		return ;
}
void	execute_simple_command(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		my_execve(cmd);
	}
	waitpid(pid, NULL, 0);
	return ;
}
int	number_of_command(t_cmd *cmd)
{
	int		i;
	t_cmd	*start;

	i = 0;
	start = cmd;
	while(start)
	{
		if (start->cmd)
			i++;
		start = start->next;
	}
	return (i);
}
t_cmd	*get_next_cmd(t_cmd *cmd)
{
	while(cmd && !cmd->cmd)
			cmd = cmd->next;
	return (cmd);
}
void	first_child(t_cmd *cmd)
{
	// (verifier files)
	// premier in stdin out newpipe[0]
}
void	mid_child(t_cmd *cmd)
{
	// (verifier files)
	// milieu in olpipe[1] out newpipe[0]
}
void	last_child(t_cmd *cmd)
{
	// (verifier files)
	// fin in oldpipe[0] out newpipte[1]
}
void	execute_pipeline(t_cmd *cmds, int size)
{
	pid_t	pid[size];
	t_cmd	*cmd;
	int		i;
	int		fd;

	i = 0;
	cmd = cmds;
	while (pid[i])
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i == 1)
				first_child(cmd);
			else if (i == size)
				last_child(cmd);
			else
				mid_child(cmd);
		}
		cmd = get_next_cmd(cmd);
		i++;
	}	
}

int	get_last_index(char **files)
{
    int i = 0;

	if (!files)
		return (-1);
    while (files[i])
        i++;
    return (i - 1);
}

void run_commands(t_cmd *cmds)
{
    t_cmd *cmd;
	int		i;

    if (cmd == NULL)
        return;
    cmd = cmds;
	i = number_of_command(cmds);
	cmds = get_next_cmd(cmds);
	if (!cmds->next || i == 1)
		execute_simple_command(cmd);
	else
		execute_pipeline(cmd, i);
	return ;
}

// pipe sur la premierre commande 
// derniere cmd ??? sinon ppipe puis fork puis execve
