/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:59:54 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/13 09:42:29 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(const char *file)
{
	int	fdin;

	if (isdigit(file[0] ) && !file[1])
		fdin = atoi(file);
	else
		fdin = open(file, O_RDONLY);
	if (fdin != -1)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	return ;
}

void	redirect_output(const char *file)
{
	int	fdout;
	
	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout != -1)
	{	
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	return ;
}

void	redirect_output_append(const char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fdout != -1)
	{	
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	return ;
}

void	redirect_heredoc(const char *delimiter)
{
	char	*line;
	int		pipefd[2];

	line = NULL;
	pipe(pipefd);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
}
