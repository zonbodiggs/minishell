/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/13 16:42:37 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_pipe(t_minishell *mini)
{
	bool	free;
	t_cmd	*tmp;

	free = true;
	tmp = mini->input->next;
	while (mini->input && !mini->input->pipe)	
	{
		if (mini->input->cmd)
			free = false;	
		redirect(mini);
		if (free)
		{
			tmp = mini->input->next;
			free_one_input(mini->input);
			mini->input = tmp;
		}
		else
			mini->input = mini->input->next;
	}
	if (mini->input && mini->input->pipe)
		redirect(mini);
	return ;
}

int		exit_error_exec(t_minishell *mini)
{
	//char	*str;

	//if (!cmd)
	//	exit (0);
	//str = strerror(errno);
	//if (cmd && cmd->cmd)
	//	perror(cmd->cmd[0]);
	//ft_printf_fd(2, "%s\n", str);
	//free_one_input(cmd);
	kill_shell(mini);
	exit(errno);
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

void	exec_builtin(t_minishell *mini, t_cmd *cmd)
{
	sort_cmd(cmd->cmd, mini->env);
	kill_shell(mini);
	exit(0);
}

int		my_execve(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = get_pipe_comd(mini->input);
	redirect_pipe(mini);
	mini->input = cmd;
	if (cmd && cmd->cmd && isbuiltin(cmd->cmd[0]) == true)
		exec_builtin(mini, cmd);
	if (!cmd || !cmd->cmd || (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1))
		return (exit_error_exec(mini)); // utiliser sterrno and perror pour message d'erreur
	return (0);
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

int		execute_simple_command(t_minishell *mini)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		close_all(fd, NULL);
		my_execve(mini);
	}
	close_all(fd, NULL);
	while (wait(NULL) > 0)
		;
	return (0);
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

bool	is_last_cmd(t_cmd	*cmd)
{
	if (!cmd->next)
		return (true);
	cmd = cmd->next;
	while(cmd)
	{
		if (cmd->cmd)
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

void	child(t_minishell *mini, int oldfd[2], int newfd[2])
{
	t_cmd *cmd;

	cmd = mini->input;
	if (oldfd[0] == -1 && oldfd[1] == -1)
		dup2(newfd[1], STDOUT_FILENO);
	else if (is_last_cmd(cmd))
		dup2(oldfd[0], STDIN_FILENO);
	else
	{
		dup2(oldfd[0], STDIN_FILENO);
		dup2(newfd[1], STDOUT_FILENO);
		close(oldfd[0]);
		close(newfd[1]);
	}
	close(newfd[0]);
	close(newfd[1]);
	if (oldfd[0] != -1)
		close(oldfd[0]);
	my_execve(mini);
}

void		init_fds(int oldfd[2], int newfd[2])
{
	ft_memset(oldfd, -1, 2 * sizeof(int));
	ft_memset(newfd, -1, 2 * sizeof(int));
}

void	update_pipeline(int *oldfd, int *newfd)
{
	if (oldfd[0] >= 0)
		close(oldfd[0]);
	oldfd[0] = newfd[0];
	oldfd[1] = newfd[1];
	close(newfd[1]);
}

t_cmd	*get_next_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while(cmd && !cmd->pipe)
	{
		
		cmd = tmp;
		if (tmp)
			tmp = tmp->next;
	}
	if (tmp)
	{
		tmp = tmp->next;
		free_one_input(cmd);
		cmd = tmp;
	}
	return (cmd);
}

int		execute_pipeline(t_minishell *mini)
{
	pid_t	pid;
	t_cmd	*for_free;
	int		oldfd[2];
	int		newfd[2];

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
	while(wait(NULL) > 0)
		;
	close_all(newfd, oldfd);
	return (0);
}

char *run_commands(t_minishell *mini)
{
	int		i;
	int		exit_code;

	exit_code = 0;
	if (!mini->input)
        return (0);
	i = number_of_command(mini->input);
	if (!mini->input->next || i == 1)
		exit_code = execute_simple_command(mini);
	else
		exit_code = execute_pipeline(mini);
	return (ft_itoa(exit_code));
}
