/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:56:32 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/11 13:56:41 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	list_env_vars(char **env)
{
	int i;
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

static int	validate_variable(char *var)
{
	char *equal_sign;
	
	equal_sign = ft_strchr(var, '=');
	if (equal_sign == NULL)
	{
		printf("export: `%s`: not a valid identifier\n", var);
		return 0;
	}
	return 1;
}

static int	update_existing_var(char *new_var, char ***env)
{
	char	*equal_sign;
	int	i;
	
	i = 0;
	equal_sign = ft_strchr(new_var, '=');
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], new_var, equal_sign - new_var) == 0 && (*env)[i][equal_sign - new_var] == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(new_var);
			return 1;
		}
		i++;
	}
	return 0;
}

static int add_new_var(char *new_var, char ***env)
{
	int	env_size;
	int	i;
	char	**new_env;

	i = 0;
	env_size = 0;
	while ((*env)[env_size] != NULL)
		env_size++;
	new_env = malloc((env_size + 2) * sizeof(char *));
	if (new_env == NULL)
	{
		perror("malloc");
		return 0;
	}
	while (i < env_size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[env_size] = ft_strdup(new_var);
	new_env[env_size + 1] = NULL;
	free(*env);
	*env = new_env;
	return 1;
}

int	export_variable(char **cmd, char ***env)
{
	char	*new_var;

	new_var = cmd[1];
	if (cmd[1] == NULL)
	{
		list_env_vars(*env);
		return 0;
	}
	if (!validate_variable(new_var))
		return 1;
	if (update_existing_var(new_var, env))
		return 0;
	if (!add_new_var(new_var, env))
		return 1;
	return 0;
}