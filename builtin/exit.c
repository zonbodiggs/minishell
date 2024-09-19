/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:56:11 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/18 15:02:03 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_numeric_arg(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] == '+' | cmd[i] == '-')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_shell(t_minishell *shell, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd[1])
	{
		exit_code = ft_atoi(cmd[1]);
		if ((exit_code == 0 && cmd[1][0] != '0') || (!is_numeric_arg(cmd[1])))
		{
			ft_printf_fd(2, "exit: %s: numeric argument required\n", cmd[1]);
			exit_code = 2;
		}
		else if (cmd[2])
		{
			ft_printf_fd(2, "%s", "exit: too many arguments\n");
			return ;
		}
	}
	kill_shell(shell);
	printf("%syou are going to exit shell 42 project from rtehar"\
	"and endoliam thanks for your time\x1b[49m\n", "\x1b[40m");
	printf("%shave good day/night :) !\x1b[49m\n", "\x1b[40m");
	printf("exit\n");
	exit(exit_code);
}
