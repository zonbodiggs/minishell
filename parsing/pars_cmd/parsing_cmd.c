/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/13 19:02:08 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// watch access of files to list cmd;

void	pars_files(t_cmd *command)
{
	if (command->redir == HEREDOC)
			heredoc(command->files);
}
//watch access to cmd

int	iscmd(char **cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;

	if (isbuiltin(cmd[0]) == true || !ft_strncmp(cmd[0], "./", 2))
		return (0);
	if (!getenv("PATH"))
	{
		ft_printf_fd(2, "minishell : command '%s' not found\n", cmd[0]);
		return (127);
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
			return (0);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(2, "minishell : command '%s' not found\n", cmd[0]);
	free_array(path);
	return (127);
}

void	pars_cmd_list(t_cmd	*command)
{
	t_cmd	*cmd;

	cmd = command;
	if (!command)
		return ;
	while (cmd)
	{
		if (cmd->files)
			pars_files(cmd);
		cmd = cmd->next;
	}
}

int	error_files(int flag, char *file)
{
	if (flag == 2)
		ft_printf_fd(2, "minishell : can't found file '%s'\n", file);
	else if (flag == 1)
		ft_printf_fd(2, "minishell : permision to file denied '%s'\n", file);
	return (flag);
}
