/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:43:05 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/01 12:09:28 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int sort_cmd(char **cmd, char **env)
{
        int     i;

        i = 0;
        while (cmd[i])
        {
                if (ft_strncmp(cmd[i], "echo", 4) == 0 && ft_strlen(cmd[i]) == 4)
		{
                        echo(cmd);
			return 1;
		}
                else if (ft_strncmp(cmd[i], "pwd", 3) == 0 && ft_strlen(cmd[i]) == 3)
		{       
			pwd();
			return 1;
		}
//              /*if else (ft_strcmp(cmd[i], "cd") = 1)
//                      cd();
		/*else if(ft_strncmp(cmd[i], "exit", 4) == 0)
			return 1;*/
                else if (ft_strncmp(cmd[i], "env", 3) == 0 && ft_strlen(cmd[i]) == 3)
		{	
			env_shell(env);
			return 1;
		}
//              if else (ft_strcmp(cmd[i], "unset") = 1)
//                      unset();
		else if (ft_strncmp(cmd[i], "export", 6) == 0 && ft_strlen(cmd[i]) == 6)
		{
			export_variable(cmd, &env);
			return 1;
		}
//              //else
//              //      exec();
                i++;
        }
	return 0;
}