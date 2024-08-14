/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtehar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:31:23 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/14 14:32:54 by rtehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	put_new_env(char **new_env, char ***env, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i != index)
		{
			new_env[j] = (*env)[i];
			j++;
		}
		else
			free((*env)[i]);
		i++;
	}
	return (j);
}

static void	remove_var(char ***env, int index)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(i * sizeof(char *));
	if (!new_env)
	{
		perror("malloc");
		return ;
	}
	i = put_new_env(new_env, env, index);
	new_env[i] = NULL;
	free(*env);
	*env = new_env;
}

static int	find_var_index(char **env, const char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	unset_variable(char **cmd, char ***env)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	while (cmd[i])
	{
		index = find_var_index(*env, cmd[i]);
		if (index != -1)
			remove_var(env, index);
		else
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd(": not found\n", STDERR_FILENO);
		}
		i++;
	}
	return (0);
}
