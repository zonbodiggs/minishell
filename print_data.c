/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:23:43 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/29 15:03:04 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printfds(t_cmd *cmd, int *old, int *new)
{
	printf("------------------fds-------------------------");
	printf("\n");
	printf("for cmd = %s at adress = %p fds : old at address = %p [0] = %d [1] = %d, new at address = %p [0] = %d [1] = %d", cmd->cmd[0], cmd->cmd, old, old[0], old[1], new, new[0], new[1]);
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	printf("------------------cmds-------------------------");
	printf("\n");
	while (cmd)
	{
		printf("adress list = %p ", cmd);
		int	i =	-1;
		if (cmd->cmd)
		{
			printf("adress cmd = %p ", cmd->cmd);
			while(cmd->cmd[++i])
				printf("cmd[%d] = %s ", i, cmd->cmd[i]);
			printf("\n");
		}
		i=-1;
		if (cmd->files)
		{
			printf("adress files = %p ", cmd->files);
			if (cmd->redir == IN)
				printf("INFILE = ");
			else if (cmd->redir == APPEND)
				printf("OUTFILE APPEND = ");
			else if (cmd->redir == TRUNC)
				printf("OUTFILE TRUNC = ");
			else if (cmd->redir == HEREDOC)
				printf("OUTFILE HEREDOC = ");
			printf("files = %s ", cmd->files);
			printf("\n");
		}
		if (cmd->pipe == true)
			printf("there is pipes after\n");
		cmd = cmd->next;
	}
	
	//print_env(cmd->t_env);
}

void	print_lexer(t_lexer *lex)
{
	if (!lex)
		return ;
	printf("------------------lexer-------------------------");
	printf("\n");
	printf("adress list = %p ", lex);
	while(lex)
	{
		if (lex->contain)
			printf("contain at adress %p = %s ", lex->contain, lex->contain);
		printf("type of lex is %d ", lex->lex);
		printf("is space after ? %d ", lex->spaces);
		printf("\n");
		lex = lex->next;
	}
}
void	print_minishell(t_minishell *mini)
{
	t_cmd *cmd = mini->input;
	t_lexer *lex = mini->lex;
	if (cmd)
	{
		while (cmd)
		{
			print_cmd(cmd);
			cmd = cmd->next;
		}
	}
	if (lex)
	{
		while (lex)
		{
			print_lexer(lex);
			lex = lex->next;
		}
		
	}
}

void	print_env(char **env)
{
	printf("------------------ENVIRONEMENT-------------------------");
	printf("\n");
	if (!env)
		return ;
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
