/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:23:43 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/07 10:45:04 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printfds(t_cmd *cmd, int *old,int *new)
{
	printf("------------------fds-------------------------");
	printf("\n");
	printf("for cmd = %s at adress = %p fds : old at address = %p [0] = %d [1] = %d, new at address = %p [0] = %d [1] = %d", cmd->cmd[0], cmd->cmd, old, old[0], old[1], new, new[0], new[1]);
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	printf("------------------cmds-------------------------");
	printf("adress list = %p", cmd);
	int	i =	0;
	if (cmd->cmd)
	{
		printf("adress cmd = %p", cmd->cmd);
		while(cmd->cmd[++i])
			printf("cmd[%d] = %s ", i, cmd->cmd[i]);
		printf("\n");
	}
	i=0;
	if (cmd->files)
	{
		printf("adress files = %p", cmd->files);
		if (cmd->redir == IN)
			printf("INFILE = ");
		else if (cmd->redir == APPEND)
			printf("OUTFILE APPEND = ");
		else if (cmd->redir == TRUNC)
			printf("OUTFILE TRUNC = ");
		else if (cmd->redir == HEREDOC)
			printf("OUTFILE HEREDOC = ");
		while(cmd->files[++i])
			printf("files[%d] = %s ", i, cmd->files[i]);
		printf("\n");
	}
}
