/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/11 14:09:13 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd **cmd)
{
	if ((*cmd)->cmd)
		free_array((*cmd)->cmd);
	if ((*cmd)->files)
		free_array((*cmd)->files);
	if ((*cmd)->t_env)
		free_array((*cmd)->t_env);
}

t_cmd	*redirect(t_cmd *cmd)
{
	int 	i;
	t_cmd	*tmp;

	tmp = cmd;
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
		tmp = tmp->next;
		free_cmd(&cmd);
		if (tmp->files)
			tmp = redirect(tmp);
	}
	return (cmd);
}
void	exit_error_exec(t_minishell *mini)
{
	free_cmd(&mini->input);
	free(mini->input);
	free_array(mini->env);
	ft_memset(mini, 0, sizeof(mini));
	free(mini);
	rl_clear_history();
	exit(147);
}
void	my_execve(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = mini->input;
	if (mini->input->files)
		mini->input = redirect(mini->input);
	if(sort_cmd(mini->input->cmd, mini->env) == 1 )
	{
		free_cmd(&mini->input);
		free(mini->input);
		free_array(mini->env);
		ft_memset(mini, 0, sizeof(mini));
		free(mini);
		rl_clear_history();
		exit(1);
	}
	if (execve(cmd->cmd[0], cmd->cmd, cmd->t_env) == -1)
		exit_error_exec(mini);
	// utiliser sterrno and perror pour message d'erreur
}

void	execute_simple_command(t_minishell *mini)
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
	if (oldfd[0] == -1 && oldfd[1] == -1) // premier set out but not in
		dup2(newfd[1], STDOUT_FILENO);
	else if (is_last_cmd(cmd)) // fin  set in but not out
		dup2(oldfd[0], STDIN_FILENO);
	else // milieu  set both of them
	{
		dup2(oldfd[0], STDIN_FILENO);
		dup2(newfd[1], STDOUT_FILENO);
	}
	close(newfd[0]);
	close(newfd[1]);
	my_execve(mini);
	// child
}


void		init_fds(int oldfd[2], int newfd[2])
{
	ft_memset(oldfd, -1, 2 * sizeof(int));
	ft_memset(newfd, -1, 2 * sizeof(int));
}


int		execute_pipeline(t_minishell *mini)
{
	pid_t	pid;
	int		oldfd[2];
	int		newfd[2];
	t_cmd	*tmp;

	init_fds(oldfd, newfd); // init fd -1
	pipe(newfd);
	tmp = mini->input;
	while (mini->input)
	{
		tmp = tmp->next;
		pid = fork();
		if (pid == 0)
			child(mini, oldfd, newfd);
		oldfd[0] = newfd[0];
		oldfd[1] = newfd[1];
		close(newfd[1]);
		pipe(newfd);
		free_cmd(&mini->input);
		free(mini->input);
		mini->input = tmp;
	}
	close(oldfd[0]);
	close(oldfd[1]);
	close(newfd[0]);
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


void run_commands(t_minishell *mini)
{
	int		i;

	if (!mini->input)
        return;
	i = number_of_command(mini->input);
	if (!mini->input->next || i == 1)
		execute_simple_command(mini);
	else
		execute_pipeline(mini);
	return ;
}

// pipe sur la premierre commande 
// derniere cmd ??? sinon ppipe puis fork puis execve
