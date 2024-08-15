/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:59:54 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/15 15:02:02 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_input(t_minishell *mini)
{
	int	fdin;

	if (isfilevalid_in(mini->input->files) != 0)
		return (error_files(isfilevalid_in(mini->input->files)
				, mini->input->files));
	fdin = open(mini->input->files, O_RDONLY);
	if (fdin == -1)
		exit_error_exec(mini, 0);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (0);
}

int	redirect_output(t_minishell *mini)
{
	int	fdout;

	if (isfilevalid_out(mini->input->files) != 0)
		return (error_files(isfilevalid_in(mini->input->files)
				, mini->input->files));
	fdout = open(mini->input->files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		exit_error_exec(mini, 0);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}

int	redirect_output_append(t_minishell *mini)
{
	int	fdout;

	fdout = open(mini->input->files, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fdout == -1)
		exit_error_exec(mini, 0);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}

int	redirect(t_minishell *mini)
{
	int		exit;

	exit = 0;
	if (mini->input && mini->input->redir)
	{
		if (mini->input->redir == IN)
			exit = redirect_input(mini);
		else if (mini->input->redir == TRUNC)
			exit = redirect_output(mini);
		else if (mini->input->redir == APPEND)
			exit = redirect_output_append(mini);
		else if (mini->input->redir == HEREDOC)
			exit = redirect_heredoc(mini);
	}
	return (exit);
}
