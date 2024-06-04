/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:45:22 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/03 14:13:14 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// init command list

void	lst_init_cmd(char **env, t_cmd **command)
{
	t_cmd	*data;

	data = ft_calloc(1, sizeof(t_cmd));
	if (!data)
		exit_cmd("allocation t_cmd failed\n");  // free and exit 
	ft_memset(data, 0, sizeof(t_cmd));
	cpy_env(env, data);
	add_cmd(command, data);
}

void	add_cmd(t_cmd **command, t_cmd *element)
{
	if (!*command)
		*command = element;
	else
	{
		while ((*command)->next)
			*command = (*command)->next;
		(*command)->next = element;
		(*command) = (*command)->next;
	}
}

