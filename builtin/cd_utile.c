/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtehar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:43:15 by rtehar            #+#    #+#             */
/*   Updated: 2024/08/14 14:45:58 by rtehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (chdir(path) != 0)
	{
		print_error(path);
		return (1);
	}
	if (update_oldpwd(env) != 0 || update_pwd(env) != 0)
	{
		ft_putendl_fd("cd: error updating environment variables",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}
