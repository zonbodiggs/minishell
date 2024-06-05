/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/05 16:13:09 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_execve(t_cmd *cmd)
{
	if (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
		return ; // free and exit
	// utiliser sterrno and perror pour message d'erreur
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

void	child(t_cmd *cmds, int oldfd[2], int newfd[2])
{
	t_cmd *cmd;

	cmd = cmds;
	ft_printf_fd(2, "fds %d %d %d %d\n",oldfd[0], oldfd[1], newfd[0], newfd[1]);
	if (oldfd[0] == -1 && oldfd[1] == -1) // premier set out but not in
	{
		// verifier enum in and out
		// in->stdin 
		dup2(newfd[1], STDOUT_FILENO); // out->newfd[0]
		ft_printf_fd(2, "cmd start %s\n",cmd->cmd[0]);
	}
	else if (!cmd->next) // fin  set in but not out
	{
		// verifier enum in and out
		dup2(oldfd[0], STDIN_FILENO); // in->oldpipe[0]
		
		// out->stdout
		ft_printf_fd(2, "cmd last %s\n",cmd->cmd[0]);
	}
	else // milieu  set both of them
	{
		// verifier enum in and out
		dup2(oldfd[0], STDIN_FILENO); // in->olpipe[1]
		
		dup2(newfd[1], STDOUT_FILENO); // out->newfd[0]
	}
	close(newfd[0]);
	close(newfd[1]);
	my_execve(cmd);
	// child
}

// void	mid_child(t_cmd *cmd)
// {
// 	// (verifier files)
// 	
// }
// void	last_child(t_cmd *cmd)
// {
// 	// (verifier files)
// 
// }

void		init_fds(int oldfd[2], int newfd[2])
{
	ft_memset(oldfd, -1, 2 * sizeof(int));
	ft_memset(newfd, -1, 2 * sizeof(int));
}

void	execute_pipeline(t_cmd *cmds)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		i;
	int		oldfd[2];
	int		newfd[2];

	i = 0;
	init_fds(oldfd, newfd); // init fd -1
	printf("fds %d %d %d %d\n",oldfd[0], oldfd[1], newfd[0], newfd[1]);
	cmd = cmds;
	pipe(newfd);
	while (cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			// init fd
			child(cmd, oldfd, newfd);
		}
		oldfd[0] = newfd[0];
		oldfd[1] = newfd[1];
		cmd = cmd->next;
		i++;
	}
	while (wait(NULL) < 0);
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
	cmds = get_next_cmd(cmds);
	if (!cmds->next || i == 1)
		execute_simple_command(cmd);
	else
		execute_pipeline(cmd);
	return ;
}

// pipe sur la premierre commande 
// derniere cmd ??? sinon ppipe puis fork puis execve

// ls | cat | rev