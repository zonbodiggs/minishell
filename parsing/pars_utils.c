/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:04:15 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/22 16:52:19 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_failure(char *msg, char c)
{
	ft_printf_fd(2, "minishell error: %s ", msg);
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
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
// printf_fd and exit correctly 

void	exit_cmd(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (47);
}

// copy environement and add it to command list

char	**cpy_env(char **env)
{
	int		len;	
	int		i;
	char	**dest;

	i = 0;
	len = 0;
	if (!env)
		return (NULL);
	while (env[len])
		len++;
	dest = malloc((len + 1) * sizeof(char *));
	while (i <= len && env[i])
	{
		dest[i] = ft_strdup(env[i]);
		if (!dest[i])
			exit_cmd("allocation env failed\n");
		i++;
	}
	dest[len] = NULL;
	return (dest);
}
