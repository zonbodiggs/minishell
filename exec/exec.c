/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/04 11:43:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_cmd *cmd)
{
	// int fd[2];
	pid_t	pid;

	pid = fork();
	// pipe(fd);
	if (pid == 0)
	{
		if (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
			return ;
	}
	else 
		waitpid(pid, NULL, 0);
	return ;
}

void	execute_pipeline(t_cmd *cmds)
{
	int		fd[2];
	pid_t	pid;
	int		infile;
	t_cmd	*cmd;
	
	cmd = cmds;
	infile = STDIN_FILENO;
	pid = fork();
	while (cmd)
	{
		pipe(fd);
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(infile, STDIN_FILENO);
				if (cmd->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			execute_command(cmd);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			infile = fd[0];
			cmd = cmd->next;
		}
	}
}

int get_last_index(char **files)
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
    int i;

    i = get_last_index(cmds->files);
    if (cmds == NULL)
        return;
    cmd = cmds;
    while (cmd)
    {
		if (i > -1)
        {
			if (cmd->redir == IN)
            redirect_input(cmd->files[i]);
		else if (cmd->redir == TRUNC)
			redirect_output(cmd->files[i]);
		else if (cmd->redir == APPEND)
			redirect_output_append(cmd->files[i]);
		else if (cmd->redir == HEREDOC)
        	redirect_heredoc(cmd->files[i]);
		}
        if (cmd->next == NULL)
            execute_command(cmd);
        else
            execute_pipeline(cmd);
        cmd = cmd->next;
    }
}

