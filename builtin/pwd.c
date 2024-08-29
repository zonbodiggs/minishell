/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/26 16:03:25 by rtehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[1])
	{
		if (cmd[1][0] == 45 && cmd[1][1] != '\0')
		{
			if (cmd[1][1] != 45 || cmd[1][2] != '\0')
			{
				printf("%s\n", "invalid option");
				return (2);
			}
		}
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		return (1);
	return (0);
}
