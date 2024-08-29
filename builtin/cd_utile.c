/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtehar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:43:15 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/26 18:05:35 by rtehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(char *path, char ***env)
{
	if (!path)
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (ft_strncmp(path, "-", ft_strlen(path) == 0))
	{
		path = get_env_value(*env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	return (path);
}

int	check_env(char ***env, const char *var, char *new_var, int len)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, len) == 0 && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return (0);
		}
		i++;
	}
	return (i);
}

int	update_pwd(char ***env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	return (set_env_var(env, "PWD", cwd));
}

int	update_oldpwd(char ***env)
{
	char	*oldpwd;

	oldpwd = get_env_value(*env, "PWD");
	if (oldpwd)
		return (set_env_var(env, "OLDPWD", oldpwd));
	return (0);
}

int	cheking_cd(char ***env, char *path)
{
	char	*oldpwd;

	if (access(".", X_OK) != 0)
	{
		oldpwd = get_env_value(*env, "OLDPWD");
		if (oldpwd && chdir(oldpwd) == 0)
		{
			ft_putendl_fd(oldpwd, STDOUT_FILENO);
			update_pwd(env);
			return (0);
		}
		return (print_error("No such file or directory"));
	}
	if (chdir(path) != 0)
		return (print_error(path));
	if (update_oldpwd(env) != 0 || update_pwd(env) != 0)
	{
		ft_putendl_fd("cd: error updating environment variables",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}
