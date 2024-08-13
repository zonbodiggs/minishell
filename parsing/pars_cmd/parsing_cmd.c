/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 01:32:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_and_check(char **cmd, t_minishell *mini)
{
	int		i;
	char	**path;
	char	*cmd_path;

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

int	iscmd(char **cmd, t_minishell *mini)
{
	if (isbuiltin(cmd[0]) == true || !ft_strncmp(cmd[0], "./", 2))
		return (0);
	if (!cmd || !mygetenv("PATH", *mini))
		return (127);
	return (set_and_check(cmd, mini));
}

int	error_files(int flag, char *file)
{
	if (flag == 2)
		ft_printf_fd(2, "minishell :'%s' No such file or directory\n", file);
	else if (flag == 1)
		ft_printf_fd(2, "minishell : permision denied %s\n", file);
	return (flag);
}
