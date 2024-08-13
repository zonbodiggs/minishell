/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:43:01 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/13 16:44:04 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		heredoc(const char *delimiter)
{
	char	*line;
	int		fd;

	line = NULL;
	fd =  open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_printf_fd(2, "delimiteur = %s\n", delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
void	redirect_heredoc(t_minishell *mini)
{
	int	fdhere;

	fdhere = open(".heredoc", O_RDONLY);
	if (fdhere == -1)
		exit_error_exec(mini);
	dup2(fdhere, STDIN_FILENO);
	close(fdhere);
	unlink(".heredoc");
	return ;
}