/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:04:15 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/26 15:52:47 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_failure(char *msg, char c)
{
	ft_printf_fd (2, "[%s2\x1b[5;0m] : %s %s", "\x1b[5;31m",
		"\x1b[1;35mminishell error\x1b[0m :", msg);
	if (c)
		ft_printf_fd (2, " << %c >>", c);
	ft_printf_fd(2, "\n");
	if (!c)
		return (-2);
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

char	**cpy_env(t_minishell *mini, char **env)
{
	int		len;	
	int		i;
	char	**dest;

	i = 0;
	len = 0;
	if (!env || !*env)
		return (NULL);
	while (env[len])
		len++;
	dest = malloc((len + 1) * sizeof(char *));
	while (i <= len && env[i])
	{
		dest[i] = ft_strdup(env[i]);
		if (dest[i] == NULL)
			exit_cmd("allocation env failed\n", mini, 2);
		i++;
	}
	dest[len] = NULL;
	return (dest);
}

void	clean_expand(char *contain)
{
	int	i;

	i = 0;
	while (contain && contain[i])
	{
		if (contain[i] && contain[i] < 0)
			contain[i] = '$';
		i++;
	}
	return ;
}
