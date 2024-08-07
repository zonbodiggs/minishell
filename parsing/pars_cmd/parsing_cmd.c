/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/01 15:30:22 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_file(char *files, int flag)
{
	if (!files)
		return (0);
	if (flag == 1)
	{
		if (isfilevalid_in(files) != 0)
			return (error_files(isfilevalid_in(files), files));
	}
	else if (flag == 2)
	{
		if (isfilevalid_in(files) != 0)
			return (error_files(isfilevalid_in(files), files));
	}
	else if (flag == 3)
	{
		if (isfilevalid_out(files) != 0)
			return (error_files(isfilevalid_out(files), files));
	}
	return (0);
}

// watch access of files to list cmd;

void	pars_files(t_cmd *command)
{
	if (command->redir == IN || command->redir == HEREDOC)
	{
		if (command->redir == IN)
			set_file(command->files, 1);
		else
			heredoc(command->files);
	}
	else if (command->redir == TRUNC || command->redir == APPEND)
	{
		if (command->redir == TRUNC)
			set_file(command->files, 3);
		else
			set_file(command->files, 4);
	}
}
//watch access to cmd

int	iscmd(char **cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;

	if (isbuiltin(cmd[0]) == true || !ft_strncmp(cmd[0], "./", 2))
		return (1);
	if (!getenv("PATH"))
	{
		ft_printf_fd(2, "minishell : command '%s' not found\n", cmd[0]);
		return (0);
	}
	i = 0;
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (0);
	while (path[i])
	{
		cmd_path = ft_slash_strjoin(path[i], cmd[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = ft_strdup(cmd_path);
			free(cmd_path);
			free_array(path);
			return (1);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(2, "minishell : command '%s' not found\n", cmd[0]);
	free_array(path);
	return (0);
}
// parsing files and cmd of any commad list

void	pars_cmd_list(t_cmd	*command)
{
	t_cmd	*cmd;
	int		j;

	cmd = command;
	if (!command)
		return ;
	j = 1;
	while (cmd)
	{
		if (cmd->files)
			pars_files(cmd);
		if (cmd->cmd)
			iscmd(cmd->cmd);
		j++;
		cmd = cmd->next;
	}
}

int	error_files(int flag, char *file)
{
	if (flag == -2)
		ft_printf_fd(2, "minishell : can't found file '%s'\n", file);
	else if (flag == -3)
		ft_printf_fd(2, "minishell : permision to file denied '%s'\n", file);
	return (-2);
}
