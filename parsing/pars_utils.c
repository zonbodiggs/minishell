/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:04:15 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/04 13:34:00 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_failure(char *msg, char c)
{
	ft_printf_fd(2,"minishell error: %s", msg);
	if (c)
		ft_printf_fd(2, "%c", c);
	ft_printf_fd(2, "\n");
	return (-1);
}

int	zap_quote(char *s, char quote, int i)
{
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] != quote)
		return (0);
	return (i);
}
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
}
// void	free_cmd(t_cmd *cmd)
// {
// 	while (cmd->next)
// 	{
// 		free_array(cmd->cmd)
// 		cmd = cmd->next;
// 	}
// }
void	exit_cmd(char *msg)
{
	ft_putstr_fd(msg, 2); // printf_fd and exit correctly 
	exit (47);
}