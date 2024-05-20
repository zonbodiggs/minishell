/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:36:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/20 20:42:55 by endoliam         ###   ########lyon.fr   */
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

void	cpy_env(char **env, t_cmd *command)
{
	int		len;	
	int		i;

	i = 0;
	len = 0;
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
	cmd = ft_calloc(len, sizeof(char *));
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
void	set_input(t_cmd *command, t_lexer *lex)
{
	if (lex->lex == INPUT)
	{
		if (ft_strncmp(lex->contain, "<<", 2) == 2)
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
void	pars_cmd(t_cmd	**command)
{
	t_cmd	*cmd;
	int		i;	

	cmd = *command;
	i = 0;
	while (cmd)
	{
		if (cmd->redir == IN)
		{
			while (cmd->files.files && cmd->files.files[i]) // leak
			{
				if (access(cmd->files.files[i], F_OK) == -1)
				{
					exit_cmd("files not found\n"); // exit correctly
					break ;
				}
				if (access(cmd->files.files[i], R_OK) == -1)
				{	
					exit_cmd("files permision denied\n"); // exit correctly
					break ;
				}
				i++;
			}
			printf("%s\n", cmd->files.files[i - 1]);
			cmd->files.fd[0] = open(cmd->files.files[i - 1], O_RDONLY);
		}
		cmd = cmd->next;
	}
}
t_cmd	*init_cmd(char **env, t_lexer *lex)
{
	t_cmd *command;
	t_cmd	*start;
	int		i;

	if (!lex)
		return (NULL);
	command = NULL;
	i = 0;
	while (lex)
	{	
		i++;
		lst_init_cmd(env, &command);
		if ((lex && lex->lex != PIPES && lex->lex != INPUT && lex->lex != OUTPUT))
		{
			command->cmd = init_command(lex);
			while (lex && lex->lex != PIPES
					&& lex->lex != INPUT && lex->lex != OUTPUT)
				lex = lex->next;
		}
		if (lex && (lex->lex == INPUT || lex->lex == OUTPUT))
		{
			set_input(command, lex);
			if (lex->next)
				lex = lex->next;
			if (lex)
				command->files.files = init_command(lex);
			while (lex && lex->lex != PIPES
				&& lex->lex != INPUT && lex->lex != OUTPUT)
				lex = lex->next;
		}
		if (i == 1)
			start = command;
		if (lex && lex->next && lex->lex != INPUT && lex->lex != OUTPUT)
			lex = lex->next;
	}
	command = start;
	pars_cmd(&command);
	return (command);
}
