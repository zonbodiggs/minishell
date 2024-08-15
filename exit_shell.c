/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:57:47 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/15 16:37:15 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer_error_exit(int i, t_lexer *lexer, t_minishell *mini)
{
	free_lexer(&lexer);
	if (i == -2)
	{
		kill_shell(mini);
		exit(2);
	}
	else
	{
		free_lexer(&mini->lex);
		free_lexer(&lexer);
		if (mini->exit_code)
			free(mini->exit_code);
		mini->exit_code = ft_itoa(2);
	}
	return (NULL);
}

void	kill_shell(t_minishell *shell)
{
	free_all_input(shell->input);
	free_array(shell->env);
	ft_memset(shell, 0, sizeof(shell));
	free(shell);
	rl_clear_history();
}
int	get_exit_code(t_minishell *mini, int value)
{
	char	*str;

	if (value == 0 && errno != 0)
	{
		value = errno;
		str = strerror(value);
		if (mini->input->cmd)
			ft_printf_fd(2, "minishell error : '%s' ", mini->input->cmd[0]);
		ft_printf_fd(2, "%s\n", str);
		if (value == 13)
			value = 126;
		return (value);
	}
	else if ((mini->input && mini->input->cmd && value == 127 ))
	{
		if (!ft_strncmp(mini->input->cmd[0], "./", 2)
				&& is_directory(mini->input->cmd[0] + 2))
		{	
			ft_printf_fd(2, "minishell error :'%s' is a directory\n",
				mini->input->cmd[0] + 2);
				return (126);
		}
		else
			ft_printf_fd(2, "minishell error : command '%s' not found\n",
				mini->input->cmd[0]);
	}
	return (value);
}
int	exit_error_exec(t_minishell *mini, int value)
{
	int exit_code;

	// if (value != 0 && errno !=0)
	// 	ft_printf_fd(2, "minishell error : ");
	exit_code = get_exit_code(mini, value);
	kill_shell(mini);
	exit(exit_code);
}

void		exit_cmd(char *msg, t_minishell *mini, int value)
{
	ft_putstr_fd(msg, 2);
	if (mini->lex)
		free_lexer(&mini->lex);
	if (mini->exit_code)
		free(mini->exit_code);
	kill_shell(mini);
	exit (value);
}