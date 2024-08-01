/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/01 15:13:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*redirect_pipe(t_minishell *mini)
{
	while (mini->input && !mini->input->pipe)	
		mini->input = redirect(mini);
	if (mini->input)
		redirect(mini);
	return (mini->input);
}

int		exit_error_exec(t_minishell *mini, t_cmd *cmd)
{
	char	*str;

	str = strerror(errno);
	if (cmd && cmd->cmd)
		perror(cmd->cmd[0]);
	ft_printf_fd(2, "%s\n", str);
	free_one_input(cmd);
	kill_shell(mini);
	exit(errno);
}
t_cmd	*get_pipe_comd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp && !tmp->pipe)
	{
		if (tmp->cmd)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
void	exec_builtin(t_minishell *mini, t_cmd *cmd)
{
	sort_cmd(cmd->cmd, mini->env);
	free_one_input(cmd);
	kill_shell(mini);
	exit(1);
}
int		my_execve(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = get_pipe_comd(mini->input);
	mini->input = redirect_pipe(mini);
	if (cmd && cmd->cmd && isbuiltin(cmd->cmd[0]) == true)
		exec_builtin(mini, cmd);
	if (!cmd| !cmd->cmd || (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1))
		return (exit_error_exec(mini, cmd)); // utiliser sterrno and perror pour message d'erreur
	return (127);
}

int		execute_simple_command(t_minishell *mini)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		my_execve(mini);
	}
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) > 0)
		;
	return (127);
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

void	close_all(int *newfd, int *oldfd)
{
	close(oldfd[0]);
	close(oldfd[1]);
	close(newfd[0]);
	close(newfd[1]);
}
void	update_pipeline(int *oldfd, int *newfd)
{
	if (oldfd[0] >= 0)
		close(oldfd[0]);
	oldfd[0] = newfd[0];
	oldfd[1] = newfd[1];
	close(newfd[1]);
}
int		execute_pipeline(t_minishell *mini)
{
	pid_t	pid;
	int		oldfd[2];
	int		newfd[2];
	t_cmd	*tmp;

	init_fds(oldfd, newfd);
	pipe(newfd);
	tmp = mini->input;
	while (mini->input)
	{
		tmp = tmp->next;
		pid = fork();
		if (pid == 0)
			child(mini, oldfd, newfd);
		update_pipeline(oldfd, newfd);
		pipe(newfd);
		free_one_input(mini->input);
		mini->input = tmp;
	}
	while(wait(NULL) > 0)
		;
	close_all(newfd, oldfd);
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
