/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:09:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 14:08:23 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	char *buffer;
	
	while(1)
	{
		printf("minishell : "); // print minishell
		buffer = readline("$ "); // set buffer in readline (wait for read)
		create_lexer(buffer); // check arg in the readline 
	}
}