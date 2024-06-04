/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/04 14:06:40 by endoliam         ###   ########lyon.fr   */
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
		if (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
			return ;
	}
	else 
		waitpid(pid, NULL, 0);
	return ;
}
// t_cmd	*execute_command(t_cmd *cmd)
// {
// 	int		fd[2];
// 	pid_t	id1;
// 	pid_t	id2;

// 	id1 = fork();
// 	pipe(fd);
// 	if (id1 == 0)
// 	{
// 		// redirection in
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		my_execve(cmd);
// 		exit(41);
// 	}
// 	id2 = fork();
// 	if (cmd->next)
// 	{
// 		// redirection out
// 		if (id2 == 0)
// 		{
// 			dup2(fd[0], STDIN_FILENO);
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			close(fd[1]);
// 			cmd = cmd->next;
// 			my_execve(cmd);
// 			exit(43);
// 		}
// 	}
// 	cmd = cmd->next;
// 	close(fd[1]);
// 	close(fd[0]);
// 	while (wait(NULL) > 0)
// 		;
// 	return (cmd);
// }

// void	execute_pipeline(t_cmd *cmds)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	int		infile;
// 	t_cmd	*cmd;
	
// 	cmd = cmds;
// 	infile = STDIN_FILENO;
// 	pid = fork();
// 	while (cmd)
// 	{
// 		pipe(fd);
// 		if (pid == -1)
// 			exit(EXIT_FAILURE);
// 		else if (pid == 0)
// 		{
// 			dup2(infile, STDIN_FILENO);
// 				if (cmd->next != NULL)
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			execute_command(cmd);
// 		}
// 		else
// 		{
// 			close(fd[1]);
// 			infile = fd[0];
// 			cmd = cmd->next;
// 		}
// 		waitpid(pid, NULL, 0);
// 	}
// }

int get_last_index(char **files)
{
    int i = 0;

	if (!files)
		return (-1);
    while (files[i])
        i++;
    return (i - 1);
}
bool	is_only_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (cmd->cmd)
			return (false);
		cmd = cmd->next;
	}
	return (true);
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
		// if (i > -1)
        // {
		// 	if (cmd->redir == IN)
		// 		redirect_input(cmd->files[i]);
		// 	else if (cmd->redir == TRUNC)
		// 		redirect_output(cmd->files[i]);
		// 	else if (cmd->redir == APPEND)
		// 		redirect_output_append(cmd->files[i]);
		// 	else if (cmd->redir == HEREDOC)
        // 		redirect_heredoc(cmd->files[i]);
		// }
		if (cmd->cmd && is_only_cmd(cmd->next) == true)
			execute_simple_command(cmd);
		cmd = cmd->next;
    }
	return ;
}

// pipe sur la premierre commande 
// derniere cmd ??? sinon ppipe puis fork puis execve
// (verifier files)
// premier in stdin out newpipe[0]
// milieu in olpipe[1] out newpipe[0]
// fin in oldpipe[0] out newpipte[1]