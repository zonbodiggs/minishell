/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/17 17:00:57 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	char *buffer;
	
	if (!*env || ac != 1)
		return (0);
	(void)av;
	while(1)
	{
		buffer = readline("minishell> "); 	// set buffer in readline (wait for read)
		add_history(buffer);				// clear history after
		create_lexer(buffer); 				// check arg in the readline 
	}
}