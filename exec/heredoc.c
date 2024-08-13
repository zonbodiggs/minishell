/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:43:01 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 01:16:35 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_heredoc(t_minishell *mini)
{
	int	fdhere;

	if (isfilevalid_in(".heredoc") != 0)
		return (error_files(isfilevalid_in(".heredoc"), ".heredoc"));
	fdhere = open(".heredoc", O_RDONLY);
	if (fdhere == -1)
		exit_error_exec(mini, 0);
	dup2(fdhere, STDIN_FILENO);
	close(fdhere);
	unlink(".heredoc");
	return (0);
}

void	heredoc(const char *delimiter, t_minishell *mini)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		if (is_env_var(line))
			line = init_env_var(line, *mini);
		if (fd != -1 && isfilevalid_out(".heredoc"))
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
	if (fd != -1)
		close(fd);
}

void	find_heredoc(t_cmd	*command, t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = command;
	if (!command)
		return ;
	while (cmd)
	{
		if (command->redir == HEREDOC)
			heredoc(command->files, mini);
		cmd = cmd->next;
	}
}
