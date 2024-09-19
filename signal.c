/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 22:48:58 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/16 13:19:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>

void	handle_sigint_input(int sig)
{
	g_signal = sig + 128;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	(void)sig;
}

void	handle_sigint(int sig)
{
	g_signal = sig + 128;
	rl_replace_line("", 0);
	rl_on_new_line();
	(void)sig;
}

void	set_exec_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
}

void	set_input_signal(void)
{
	signal(SIGINT, handle_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}
