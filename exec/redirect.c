/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:59:54 by rtehar            #+#    #+#             */
/*   Updated: 2024/07/29 14:45:09 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(t_minishell *mini)
{
	int	fdin;

	fdin = open(mini->input->files, O_RDONLY);
	if (fdin == -1)
		exit_error_exec(mini);;
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return ;
}

void	redirect_output(t_minishell *mini)
{
	int	fdout;

	fdout = open(mini->input->files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		exit_error_exec(mini);;
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return ;
}

void	redirect_output_append(t_minishell *mini)
{
	int	fdout;

	fdout = open(mini->input->files, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fdout == -1)
		exit_error_exec(mini);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
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
