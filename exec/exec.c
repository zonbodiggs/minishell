/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/03 16:32:31 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_cmd *cmd)
{
}
void	execute_childone(t_cmd *cmd, int fdin, int fdout)
{
	if (fdin != -1)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	if (!cmd->cmd || execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
		return ; // free and exit
}
void	execute_childtwo(t_cmd *cmd, int fdout, int fdin)
{
	if (fdout != -1)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	if (!cmd->next || cmd->next->cmd || execve(cmd->next->cmd[0], cmd->next->cmd, cmd->next->t_env) == -1)
		return ; // free and exit
}

void	execute_pipeline(t_cmd *cmds, int fdin, int fdout)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	t_cmd	*cmd;

	cmd = cmds;
	pid1 = fork();
	pid2 = fork();
	pipe(fd);
	if (pid1 == -1)
		exit(95); // free and exit
	else if (pid1 == 0)
	{
		//dup2(infile, STDIN_FILENO);
	//	if (cmd->next != NULL)
		//	dup2(fd[1], STDOUT_FILENO);
		close(fdout);
		execute_childone(cmd, fdin, fdout);
	}
	while (wait(NULL) > 0)
		;
	if (pid2 == 0)
	{
		close(fdin);
		execute_childtwo(cmd, fdout, fdin);
		//infile = fd[0];
		//cmd = cmd->next;
	}
	//waitpid(pid, NULL, 0);
}

int get_last_index(char **files)
{
    int i = 0;

	if (!files)
		return (0);
	while (files[i])
		i++;
	return (i - 1);
}

void run_commands(t_cmd *cmds)
{
	t_cmd *cmd;
	int i;
	int	fdin;
	int	fdout;

	fdin = 0;
	fdout = 0;
	i = get_last_index(cmds->files);
	if (cmds == NULL)
		return;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->files && cmd->redir == IN)
			fdin = redirect_input(cmd->files[i]);
		else if (cmd->files && cmd->redir == TRUNC)
			fdout = redirect_output(cmd->files[i]);
		else if (cmd->files && cmd->redir == APPEND)
			fdout = redirect_output_append(cmd->files[i]);
		//else if (cmd->files && cmd->redir == HEREDOC)
		//	redirect_heredoc(cmd->files[i]);
		// if ((!cmd->next) || (cmd->next && !cmd->next->cmd))
        execute_command(cmd);
        //else
		if (cmd->cmd)
			execute_pipeline(cmd, fdin, fdout);
		cmd = cmd->next;
    }
}

