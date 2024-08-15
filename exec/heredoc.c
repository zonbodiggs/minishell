/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:43:01 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 22:52:04 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_final_heredoc(t_cmd *command)
{
	t_cmd *cmd;

	if (!command)
		return (true);
	cmd = command->next;
	while (cmd)
	{
		if (cmd && cmd->redir && cmd->redir == HEREDOC)
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

int	redirect_heredoc(t_minishell *mini)
{
	int	fdhere;

	g_signal = 0;
	// SIGINT signql heredoc ioctl
	if (isfilevalid_in(".heredoc"))
		return (error_files(isfilevalid_in(".heredoc"), ".heredoc"));
	fdhere = open(".heredoc", O_RDONLY);
	if (fdhere == -1 && is_last_cmd(mini->input))
		exit_error_exec(mini, 0);
	dup2(fdhere, STDIN_FILENO);
	close(fdhere);
	if (is_final_heredoc(mini->input))
		unlink(".heredoc");
	return (0);
}

void	heredoc(const char *delimiter, t_minishell *mini)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_printf_fd(2, "delimiteur = %s\n", delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (is_env_var(line))
			line = init_env_var(line, *mini);
		if (fd != -1 || isfilevalid_out(".heredoc"))
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
		if (cmd && cmd->redir == HEREDOC)
		{
			if (access(".heredoc", F_OK) == 0)
				unlink(".heredoc");
			heredoc(cmd->files, mini);
		}
			cmd = cmd->next;
	}
}
//quote 
// ctr + c stop tout
// ctr + d stop 1seul here