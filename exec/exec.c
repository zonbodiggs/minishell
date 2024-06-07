/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/07 15:59:43 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*redirect(t_cmd *cmd)
{
	int i;

	i = get_last_index(cmd->files);
	if (cmd->redir == IN)
		redirect_input(cmd->files[i]);
	else if (cmd->redir == TRUNC)
		redirect_output(cmd->files[i]);
	else if (cmd->redir == APPEND)
		redirect_output_append(cmd->files[i]);
	else if (cmd->redir == HEREDOC)
		redirect_heredoc(cmd->files[i]);
	if (!cmd->cmd && cmd->next)
	{
		cmd = cmd->next;
		if (cmd->files)
			cmd = redirect(cmd);
	}
	return (cmd);
}
void	my_execve(t_cmd *cmd)
{
	if (cmd->files)
		cmd = redirect(cmd);
	if (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
		exit(127) ; // free and exit
	// utiliser sterrno and perror pour message d'erreur
}

void	execute_simple_command(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		close(fd[0]);	
		close(fd[1]);
		my_execve(cmd);
	}
	while (wait(NULL) > 0);
	return ;
}
int	number_of_command(t_cmd *cmd)
{
	int		i;
	t_cmd	*start;

	if (!cmd)
		return (0);
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

void	child(t_cmd *cmds, int oldfd[2], int newfd[2])
{
	t_cmd *cmd;

	cmd = cmds;
	printfds(cmd, oldfd,newfd);
	if (oldfd[0] == -1 && oldfd[1] == -1) // premier set out but not in
		dup2(newfd[1], STDOUT_FILENO);
	else if (!cmd->next) // fin  set in but not out
		dup2(oldfd[0], STDIN_FILENO);
	else // milieu  set both of them
	{
		dup2(oldfd[0], STDIN_FILENO);
		dup2(newfd[1], STDOUT_FILENO);
	}
	if (newfd[0] > 0)
		close(newfd[0]);
	if (newfd[1] > 0)
		close(newfd[1]);
	my_execve(cmd);
	// child
}


void		init_fds(int oldfd[2], int newfd[2])
{
	ft_memset(oldfd, -1, 2 * sizeof(int));
	ft_memset(newfd, -1, 2 * sizeof(int));
}

int		execute_pipeline(t_cmd *cmds)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		oldfd[2];
	int		newfd[2];

	init_fds(oldfd, newfd); // init fd -1
	pipe(newfd);
	while (cmds)
	{
		cmd = cmds;
		pid = fork();
		if (pid == 0)
			child(cmd, oldfd, newfd);
		oldfd[0] = newfd[0];
		oldfd[1] = newfd[1];
		close(newfd[1]);
		pipe(newfd);
		cmds = cmds->next;
	}
	if (oldfd[0] > 0)
		close(oldfd[0]);
	if (oldfd[1] > 0)
		close(oldfd[1]);
	if (newfd[0] > 0)
		close(newfd[0]);
	if (newfd[1] > 0)
		close(newfd[1]);
	while(wait(NULL) > 0);
	return (127);
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

    cmd = cmds;
	if (cmd == NULL)
        return;
	i = number_of_command(cmds);
	if (!cmds->next || i == 1)
		execute_simple_command(cmd);
	else
		execute_pipeline(cmd);
	return ;
}

// pipe sur la premierre commande 
// derniere cmd ??? sinon ppipe puis fork puis execve

// ls | cat | rev