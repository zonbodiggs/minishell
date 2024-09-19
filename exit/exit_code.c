/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 00:54:46 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/18 09:50:07 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_param_err(char *error, char *param)
{
	error = join_and_free(error, "<< ");
	error = join_and_free(error, param);
	error = join_and_free(error, " >> : ");
	return (error);
}

static int	find_cmd_err(char *error, int value, t_minishell *mini)
{
	char	*ptr;

	error = add_param_err(error, mini->input->cmd[0]);
	ptr = mini->input->cmd[0] + ft_strlen(mini->input->cmd[0]) - 1;
	if (!ft_strncmp(mini->input->cmd[0], "./", 2))
	{
		if (is_directory(mini->input->cmd[0] + 2))
		{
			error = ft_strjoingnl(error, "is a directory ");
			value = 126;
		}
		else
			error = ft_strjoingnl(error, "no such file or directory");
	}
	else if (!is_directory(mini->input->cmd[0]) && ft_strchr(ptr, '/'))
	{
		error = ft_strjoingnl(error, "is not a directory ");
		value = 126;
	}
	else
		error = ft_strjoingnl(error, "command not found");
	ft_printf_fd(2, "[%s%d\x1b[5;0m] %s\x1b[0m\n", "\x1b[5;31m", value, error);
	free(error);
	return (value);
}

int	get_strerro(t_minishell *mini, int value)
{
	char	*error;

	error = NULL;
	error = ft_strjoin("\x1b[1;35m", "minishell error\x1b[0m : ");
	if (value == 0 && errno != 0)
	{
		value = errno;
		if (mini->input && mini->input->cmd)
			error = add_param_err(error, mini->input->cmd[0]);
		error = ft_strjoingnl(error, strerror(value));
		if (value == 13 || value == 8)
			value = 126;
		ft_printf_fd(2, "[%s%d\x1b[5;0m] %s\x1b[0m\n",
			"\x1b[5;31m", value, error);
		free(error);
	}
	else if ((mini->input && mini->input->cmd && value == 127))
		value = find_cmd_err(error, value, mini);
	else
		free(error);
	return (value);
}

int	get_exit_code(t_minishell *mini, int value)
{
	if (value == 2)
		value = 1;
	value = get_strerro(mini, value);
	return (value);
}
