/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:13:54 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/20 17:56:06 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>
#include <string.h>

void	print_error(char *arg)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}

char	*get_env_value(char **env, const char *var)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	change_env(char ***env, char *new_var, int i)
{
	char	**new_env;
	int		size;

	size = 0;
	while ((*env)[size])
		size++;
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	i = 0;
	while (i < size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[size] = new_var;
	new_env[size + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	set_env_var(char ***env, const char *var, const char *value)
{
	int		len;
	char	*new_var;
	int		end;
	int		i;

	len = ft_strlen(var);
	new_var = malloc(len + ft_strlen(value) + 2);
	if (!new_var)
		return (-1);
	ft_strlcpy(new_var, var, ft_strlen(var) + 1);
	ft_strlcat(new_var, "=", ft_strlen(new_var) + 2);
	ft_strlcat(new_var, (char *)value,
		ft_strlen(value) + ft_strlen(new_var) + 1);
	i = check_env(env, var, new_var, len);
	if (i == 0)
		return (0);
	end = change_env(env, new_var, i);
	return (end);
}

int	cd(char **cmd, char ***env)
{
	char	*path;

	path = cmd[1];
	if (!path)
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			return (1);
		}
	}
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		path = get_env_value(*env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			return (1);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	if (cheking_cd(env, path) == 1)
		return (1);
	return (0);
}
