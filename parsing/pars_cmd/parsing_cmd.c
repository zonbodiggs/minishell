/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/16 11:44:32 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <dirent.h>

int	set_and_check(char **cmd, t_minishell *mini)
{
	int		i;
	char	**path;
	char	*cmd_path;

	i = 0;
	if (!cmd || !*cmd || !cmd[0][0])
		return (127);
	path = ft_split(mygetenv("PATH", *mini), ':');
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
	free_array(path);
	return (127);
}
bool	is_directory(char *cmd)
{
	DIR	 *dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		return (true);
	}
	return (false);
}

int	iscmd(char **cmd, t_minishell *mini)
{
	if (!cmd || !cmd[0])
		return (127);
	if (!ft_strcmp(cmd[0], "./"))
	{
		if (!is_directory(cmd[0] + 2))
			return (0);
		return (127);
	}
	else if (ft_strrchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
			return (0);
		return (127);
	}
	if (isbuiltin(cmd[0]) == true)
		return (0);	
	if (!cmd || !mygetenv("PATH", *mini))
		return (127);
	return (set_and_check(cmd, mini));
}

int	error_files(int flag, char *file)
{
	if (flag == 2)
		ft_printf_fd(2, "minishell error :'%s' No such file or directory\n", file);
	else if (flag == 1)
		ft_printf_fd(2, "minishell error :'%s' permision denied\n", file);
	return (flag);
}
