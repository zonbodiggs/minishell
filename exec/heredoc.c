/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:43:01 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/17 03:38:00 by endoliam         ###   ########lyon.fr   */
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
	if (isfilevalid_in(mini->input->files))
		return (error_files(isfilevalid_in(mini->input->files), mini->input->files));
	fdhere = open(mini->input->files, O_RDONLY);
	if (fdhere == -1)
		exit_error_exec(mini, 0);
	dup2(fdhere, STDIN_FILENO);
	close(fdhere);
	unlink(mini->input->files);
	return (0);
}
static void	write_heredoc(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}
int	heredoc(const char *delimiter, int fd, t_minishell *mini)
{
	char	*line;
	
	ft_printf_fd(2, "delimiteur = %s\n", delimiter);
	set_input_signal();
	while (g_signal != 130)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			if (!line)
			{
				printf("minishell heredoc : (wanted limiter `%s\')\n", delimiter);
				return (-1);
			}
			free(line);
			return (0);
		}
		if (is_env_var(line))
			line = init_env_var(line, *mini);
		if (fd != -1 || isfilevalid_out(".heredoc"))
			write_heredoc(fd, line);
		free(line);
	}
	return (0);
}

void	find_heredoc(t_cmd	*command, t_minishell *mini)
{
	t_cmd	*cmd;
	int		fd;
	int		i;
	char	*herename;
	char	*index;

	cmd = command;
	i = 1;
	if (!command)
		return ;
	while (cmd)
	{
		if (cmd && cmd->redir == HEREDOC)
		{
			index = ft_itoa(i);
			herename = ft_strjoin(".heredoc_", index);
			fd = open(herename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			heredoc(cmd->files, fd, mini);
			if (fd != -1)
				close(fd);
			if (g_signal == 130)
				unlink(herename);
			free(cmd->files);
			cmd->files = ft_strdup(herename);
			free(herename);
			free(index);
			i++;
		}
		cmd = cmd->next;
	}
	
}
//quote 
// ctr + c stop tout
// ctr + d stop 1 seul here