/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:57:10 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/19 11:14:04 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipeline(t_minishell *mini)
{
	t_cmd	*for_free;

	while (mini->input && !mini->input->pipe)
	{
		for_free = mini->input->next;
		free_one_input(mini->input);
		mini->input = for_free;
	}
	if (mini->input)
	{
		for_free = mini->input->next;
		free_one_input(mini->input);
		mini->input = for_free;
	}
}

void	update_pipeline(int *oldfd, int *newfd)
{
	if (oldfd[0] >= 0)
		close(oldfd[0]);
	oldfd[0] = newfd[0];
	oldfd[1] = newfd[1];
	close(newfd[1]);
}

void	close_all(int *newfd, int *oldfd)
{
	if (oldfd)
	{
		close(oldfd[0]);
		close(oldfd[1]);
	}
	if (newfd)
	{
		close(newfd[0]);
		close(newfd[1]);
	}
}
