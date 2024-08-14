/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:57:47 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/14 18:46:29 by endoliam         ###   ########lyon.fr   */
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
		mini->exit_code = ft_itoa(2);
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

int	exit_error_exec(t_minishell *mini, int value)
{
	char	*str;

	if (value == 0 && errno != 0)
	{
		value = errno;
		str = strerror(value);
		ft_printf_fd(2, "minishell : %s\n", str);
	}
	else if (value == 127)
		ft_printf_fd(2, "minishell : command '%s' not found\n",
			mini->input->cmd[0]);
	kill_shell(mini);
	exit(value);
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