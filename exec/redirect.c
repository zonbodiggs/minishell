/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:59:54 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/01 13:10:19 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(t_minishell *mini)
{
	int	fdin;

	fdin = open(mini->input->files, O_RDONLY);
	if (fdin == -1)
		exit_error_exec(mini, NULL);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return ;
}

void	redirect_output(t_minishell *mini)
{
	int	fdout;

	fdout = open(mini->input->files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		exit_error_exec(mini, NULL);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return ;
}

void	redirect_output_append(t_minishell *mini)
{
	int	fdout;

	fdout = open(mini->input->files, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fdout == -1)
		exit_error_exec(mini, NULL);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return ;
}
t_cmd	*redirect(t_minishell *mini)
{
	t_cmd	*tmp;

	tmp = mini->input;
	tmp = tmp->next;
	if (mini->input && mini->input->redir)
	{
		if (mini->input->redir == IN)
			redirect_input(mini);
		else if (mini->input->redir == TRUNC)
			redirect_output(mini);
		else if (mini->input->redir == APPEND)
			redirect_output_append(mini);
		else if (mini->input->redir == HEREDOC)
			redirect_heredoc(mini);
		if (!mini->input->cmd)
			free_one_input(mini->input);	
	}
	mini->input = tmp;
	return (mini->input);
}

