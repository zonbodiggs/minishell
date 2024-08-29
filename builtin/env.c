/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:55:59 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/26 16:03:53 by rtehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_shell(char **env, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		if (cmd[1][0] == 45)
		{
			printf("%s\n", "env : invalid option");
			return (125);
		}
		printf ("%s\n", "env: No such file or directory");
		return (127);
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != NULL)
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
