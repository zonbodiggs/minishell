/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/29 12:41:45 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// watch the 

int		set_file(char **files, int flag)
{
	int		i;

	i = 0;
	if (!files)
		return (0);
	printf("FILES SET %s\n", files[0]);
	while(files[i])
	{
		if (flag == 1)
		{
			if (isfilevalid_in(files[i]) != 0)
				return(error_files(isfilevalid_in(files[i])));
		}
		else if (flag == 2)
		{
			if (i > 0 && isfilevalid_in(files[i]) != 0)
				return(error_files(isfilevalid_in(files[i])));
		}
		else if (flag == 3)
		{
			if (isfilevalid_out(files[i]) != 0)
				return(error_files(isfilevalid_out(files[i])));
		}
		i++;
	}
	return (0);
}

// watch access of files to list cmd;

void	pars_files(t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	if (cmd->redir == IN || cmd->redir == HEREDOC)
	{
		if (cmd->redir == IN)
			set_file(cmd->files, 1);
		else
			set_file(cmd->files, 2);
	}
	else if (cmd->redir == TRUNC || cmd->redir == APPEND)
	{
		if (cmd->redir == TRUNC)
			set_file(cmd->files, 3);
		else
			set_file(cmd->files, 4);
	}
}
//watch access to cmd

void	pars_cmd(char **cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		cmd_path = ft_slash_strjoin(path[i], cmd[0]);
		if (access(cmd_path, F_OK) == 0) // check also if cmd[0] is builtin
		{
			cmd[0] = ft_strdup(cmd_path); // set cmd_path to cmd[0]
			free(cmd_path); // free cmd_path
			free_array(path); // free path
			printf("path cmd %s\n", cmd[0]);
			return ;
		}
		i++;
	}
	free(cmd_path); // free cmd_path
	free_array(path); // free path
	printf("cmd not found\n"); // error message
	return ;  // return fonction
}
// parsing files and cmd of any commad list

void	pars_cmd_list(t_cmd	*command)
{
	t_cmd	*cmd;

	cmd = command;
	if (!command)
		exit(8);
	int j = 1;
	while (cmd)
	{
		if (cmd->cmd)
			printf("COMMAND %d %s\n",j,cmd->cmd[0]);
		if (cmd->files)
			printf("FILES %d %s\n",j,cmd->files[0]);
		if (cmd->files)
			pars_files(cmd); // pars files
		if (cmd->cmd)
			pars_cmd(cmd->cmd); // add fonction that pars cmd
		j++;
		cmd = cmd->next;
	}
}

int	error_files(int flag)
{
	if (flag == -2)
		ft_putstr_fd("can't found file\n", 2); // put name of file
	else if (flag == -3)
		ft_putstr_fd("permision to file denied\n", 2); // put name of file
	return (-2);
}

// // open file and return result of open

// int	create_file(char *file, int flag)
// {
// 	if (flag <= 2)
// 		return (open(file, O_RDONLY));	// for in file
// 	else if (flag == 3)
// 		return (open(file, O_TRUNC)); // out file >
// 	else if (flag == 4)
// 		return (open(file, O_WRONLY | O_CREAT)); // out file >>
// 	return (0);
// }