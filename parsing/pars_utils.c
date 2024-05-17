/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:04:15 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/17 17:16:46 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_failure(char *msg)
{
	ft_putstr_fd(msg, 2); // exit correctly
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