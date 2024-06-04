/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:59:54 by rtehar            #+#    #+#             */
/*   Updated: 2024/06/04 13:04:11 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_input(const char *file)
{
	int	fdin;

	fdin = open(file, O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (fdin);
}

int	redirect_output(const char *file)
{
	int	fdout;

	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return(fdout);
}

int	redirect_output_append(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{	
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return(fd);
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
		if (line == NULL || ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
