/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/18 12:57:35 by endoliam         ###   ########lyon.fr   */
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
	DIR		*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		return (true);
	}
	return (false);
}

static bool	is_valid_file(char *cmd)
{
	if (is_directory(cmd))
		return (false);
	else if (access(cmd, F_OK) != 0)
		return (false);
	return (true);
}

int	iscmd(char **cmd, t_minishell *mini)
{
	if (!cmd || !*cmd || !cmd[0][0])
		return (127);
	if (!ft_strcmp(cmd[0], "minishell"))
	{
		free(cmd[0]);
		cmd[0] = ft_strdup("./minishell");
	}
	if (!ft_strncmp(cmd[0], "./", 2))
	{
		if (is_valid_file(cmd[0] + 2))
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
		ft_printf_fd(2, "[%s%d\x1b[5;0m] : %s << %s >> %s\n", "\x1b[5;31m",
			1, "\x1b[1;35mminishell error\x1b[0m :", file,
			" No such file or directory");
	else if (flag == 1)
		ft_printf_fd(2, "[%s%d\x1b[5;0m] : %s << %s >> %s\n", "\x1b[5;31m",
			flag, "\x1b[1;35mminishell error\x1b[0m :", file,
			" permision denied");
	return (flag);
}
