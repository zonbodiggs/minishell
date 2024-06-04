/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:20:21 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/04 14:14:17 by endoliam         ###   ########lyon.fr   */
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
	if (is_only_cmd(cmd->next) == true)
			execute_simple_command(cmd);
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