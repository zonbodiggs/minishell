/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:56:11 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/11 14:10:27 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd) {
        tmp = cmd;
        cmd = cmd->next;
        free_array(tmp->cmp);
	free_array(tmp->t_env);
        free_array(tmp->files);
        free(tmp);
    }
}*/

void exit_shell(t_minishell *shell, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd[1])
	{
		exit_code = ft_atoi(cmd[1]);
		if (exit_code == 0 && cmd[1][0] != '0')
		{
			printf("exit: %s: numeric argument required\n", cmd[1]);
			exit_code = 255;
		}
		else if (cmd[2])
		{
			printf("%s", "exit: too many arguments\n");
			return;
		}
	}
	free_cmd(&shell->input);
	free_array(shell->env);
	clear_history();
	printf("exit\n");
	exit(exit_code);
}