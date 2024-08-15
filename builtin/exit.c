/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:56:11 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 20:33:58 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_shell(t_minishell *shell, char **cmd)
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
			return ;
		}
	}
	kill_shell(shell);
	printf("%syou exit shell 42 project from rtehar and endoliam thanks for your time\nhave good day/night :)\n\x1b[49m", "\x1b[42m");
	printf("exit\n");
	exit(exit_code);
}
