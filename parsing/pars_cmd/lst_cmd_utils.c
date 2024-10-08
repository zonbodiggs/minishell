/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:45:22 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 15:45:49 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lst_init_cmd(t_minishell *mini, t_cmd **command)
{
	t_cmd	*data;

	data = ft_calloc(1, sizeof(t_cmd));
	if (!data)
		exit_cmd("allocation t_cmd failed\n", mini, 2);
	ft_memset(data, 0, sizeof(t_cmd));
	data->t_env = cpy_env(mini, mini->env);
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
