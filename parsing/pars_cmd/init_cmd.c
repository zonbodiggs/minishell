/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/21 18:35:52 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//bool	is_a_cmd(char *s, char **path)
//{
//	int		i;
//
//	i = 0;
//	while (path[i])
//	{
//		if (access(path[i], F_OK) == 0)
//			return (true);
//		i++;
//	}
//	return (false);
//}

void	exit_cmd(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (0);
}

void	add_cmd(t_cmd **command, t_cmd *element)
{
	if (!*command)
		*command = element;
	else
	{
		while ((*command)->next)
			*command = (*command)->next;
		(*command)->next = element;
		(*command) = (*command)->next;
	}
}
// copy environement and add it to command list

void	cpy_env(char **env, t_cmd *command)
{
	int		len;	
	int		i;

	i = 0;
	len = 0;
	if (!command)
		return ;
	while(env[len])
		len++;
	command->t_env = malloc((len + 1) * sizeof(char *));
	while(i <= len && env[i])
	{
		command->t_env[i] = ft_strdup(env[i]);
		if (!command->t_env[i])
			exit_cmd("allocation env failed\n");  // free and exit
		i++;
	}
}
// duplicate word in cmd or files.files 

char	*dup_cmd(t_lexer *lex)
{
	char	*cmd;

	if (!lex)
		return (NULL);
	if (lex->lex == SINGLE_Q || lex->lex == DOUBLE_Q)
		cmd = ft_qstrdup(lex->contain);
	else
	cmd = ft_strdup(lex->contain);
	if (!cmd)
		exit_cmd("allocation cmd failed\n"); // free and exit
	return (cmd);
}
// put array of *cmd or *files in command

char	**init_command(t_lexer *lex)
{
	int		len;
	int		i;
	char	**cmd;
	t_lexer	*tmp;

	i = 0;
	len = 0;
	tmp = lex;
	while(tmp  && tmp->lex != PIPES
			&& tmp->lex != INPUT && tmp->lex != OUTPUT)
	{
		len++;
		tmp = tmp->next;
	}
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
		exit_cmd("allocation t_cmd failed\n"); ; // free and exit 
	while (i < len)
	{
		cmd[i] = dup_cmd(lex);
		i++;
		lex = lex->next;
	}
	return (cmd);
}
// init command list

void	lst_init_cmd(char **env, t_cmd **command)
{
	t_cmd	*data;

	data = ft_calloc(1, sizeof(t_cmd));
	if (!data)
		exit_cmd("allocation t_cmd failed\n"); ; // free and exit 
	ft_memset(data, 0, sizeof(t_cmd));
	cpy_env(env, data);
	add_cmd(command, data);
}
// set enum redirection of command

void	set_input(t_cmd *command, t_lexer *lex)
{
	if (lex->lex == INPUT)
	{
		if (ft_strlen(lex->contain) == 2)
			command->redir = HEREDOC;
		else
			command->redir = IN;
	}
	else if (lex->lex == OUTPUT)
	{
		if ((ft_strlen(lex->contain) == 2))
			command->redir = APPEND;
		else if (ft_strlen(lex->contain) == 1)
			command->redir = TRUNC;
	}
}
int		isfilevalid_in(char *file)
{
	if (access(file, F_OK) == -1)
		return (-2);
	if (access(file, R_OK) == -1)
		return (-3);
	return (0);
}

int		isfilevalid_out(char *file)
{
	if (access(file, F_OK) == -1)
		return (-2);
	if (access(file, W_OK) == -1)
		return (-3);
	return (0);
}
// open file and return result of open

int	create_file(char *file, int flag)
{
	if (flag <= 2)
		return (open(file, O_RDONLY));	// for in file
	else if (flag == 3)
		return (open(file, O_TRUNC)); // out file >
	else if (flag == 4)
		return (open(file, O_WRONLY | O_CREAT)); // out file >>
	return (0);
}
int	error_files(int flag)
{
	if ((flag == -2))
		ft_putstr_fd("can't found file\n", 2); // put name of file
	else if (flag == -3)
		ft_putstr_fd("permision to file denied\n", 2); // put name of file
	return (-2);
}
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
			// set cmd_path to cmd[0]
			// free cmd_path
			// free path
			// return fonction
			return ;
		}
		i++;
	}
	// free path
	// free cmd path
	// error message 
	// return fonction
	return ;
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

// init struct list cmd

bool	isoperator_cmd(t_lexer_type lex_type)
{
	if (lex_type == PIPES
		|| lex_type == INPUT
		|| lex_type == OUTPUT)
		return (true);
	return (false);
}

t_cmd	*init_cmd(char **env, t_lexer *lex)
{
	t_cmd *command;
	t_cmd	*start;
	int		i;

	if (!lex)
		return (NULL);
	i = 0;
	command = NULL;
	start = NULL;
	while (lex)
	{	
		i++;
		lst_init_cmd(env, &command);
		if ((lex && lex->lex != PIPES && lex->lex != INPUT && lex->lex != OUTPUT))
		{
			command->cmd = init_command(lex);
			while (lex &&  lex->lex != PIPES
				&& lex->lex != INPUT && lex->lex != OUTPUT)
				lex = lex->next;
		}
		if (lex && (lex->lex == INPUT || lex->lex == OUTPUT))
		{
			set_input(command, lex);
			if (lex->next)
			{
				lex = lex->next;
				command->files = init_command(lex);
				while (lex && lex->lex != PIPES
					&& lex->lex != INPUT && lex->lex != OUTPUT)
					lex = lex->next;
			}
			else
				lex = lex->next;
		}
		if (i == 1)
			start = command;
		if (lex && lex->next && lex->lex != INPUT && lex->lex != OUTPUT)
			lex = lex->next;
	}
	command = start;
	pars_cmd(command);
	return (command);
}

// test "ls |" sigint error
// don't work if the input start