/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:48:23 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/16 12:53:31 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	update_pipeline(int *oldfd, int *newfd)
{
	if (oldfd[0] >= 0)
		close(oldfd[0]);
	oldfd[0] = newfd[0];
	oldfd[1] = newfd[1];
	close(newfd[1]);
}

void	close_all(int *newfd, int *oldfd)
{
	if (oldfd)
	{
		close(oldfd[0]);
		close(oldfd[1]);
	}
	if (newfd)
	{
		close(newfd[0]);
		close(newfd[1]);
	}
}

void	child(t_minishell *mini, int oldfd[2], int newfd[2])
{
	t_cmd	*cmd;

	//sigint 
	//sigquit vers mm fonction
	cmd = mini->input;
	if (oldfd[0] == -1 && oldfd[1] == -1)
		dup2(newfd[1], STDOUT_FILENO);
	else if (is_last_cmd(cmd))
		dup2(oldfd[0], STDIN_FILENO);
	else
	{
		dup2(oldfd[0], STDIN_FILENO);
		dup2(newfd[1], STDOUT_FILENO);
	}
	close_all(newfd, NULL);
	if (oldfd[0] != -1)
		close(oldfd[0]);
	my_execve(mini);
}
int	my_wait(int status, int pid)
{
	int exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (wait(&status) > 0)
	{
		if (waitpid(pid, &status, 0) == pid)
		{
			exit_code = status;
			i++;
		}
	}
	return (exit_code);
}
int	execute_pipeline(t_minishell *mini)
{
	pid_t	pid;
	int		status;
	t_cmd	*for_free;
	int		oldfd[2];
	int		newfd[2];

	status = 0;
	init_fds(oldfd, newfd);
	pipe(newfd);
	while (mini->input)
	{
		for_free = mini->input->next;
		pid = fork();
		if (pid == 0)
			child(mini, oldfd, newfd);
		update_pipeline(oldfd, newfd);
		pipe(newfd);
		free_one_input(mini->input);
		mini->input = for_free;
	}
	status = my_wait(status, pid);
	// init_signal ignoe sigquit redirige sigint 
	close_all(newfd, oldfd);
	return (WEXITSTATUS(status));
}

int	execute_simple_command(t_minishell *mini)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		close_all(fd, NULL);
		my_execve(mini);
	}
	close_all(fd, NULL);
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
