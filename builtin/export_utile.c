/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:35:30 by rtehar            #+#    #+#             */
/*   Updated: 2024/09/19 16:00:57 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_existing_var(char *new_var, char ***env)
{
	char	*equal_sign;
	int		i;

	i = 0;
	printf("Jsuisbien\n");
	equal_sign = ft_strchr(new_var, '=');
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], new_var, equal_sign - new_var) == 0 &&
			(*env)[i][equal_sign - new_var] == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(new_var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_var(char *new_var, char **env)
{
	int	i;

	i = 0;
	//printf("\n\n\n\n%c\n\n\n\n\n",new_var[i - 1]);
	while (env[i])
	{
		if (ft_strncmp(new_var, env[i], ft_strlen(new_var)) == 0)
		{
			env[i][0] = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_egal(char *var)
{
	int	i;

	i = 0;
	while(var[i])
	{
		if(var[i] == '=' && (i == 0 || var[i - 1] == ' '))
				return (0);
		i++;
	}
	return (1);
}

int	add_new_var(char *new_var, char ***env)
{
	int		env_size;
	int		i;
	char	**new_env;

	i = 0;
	env_size = 0;
	// if(check_var(new_var, *env) == 0)
	// 	return (1);
	check_var(new_var, *env);
	while ((*env)[env_size] != NULL)
		env_size++;
	new_env = malloc((env_size + 2) * sizeof(char *));
	if (new_env == NULL)
	{
		perror("malloc");
		return (0);
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
	return (1);
}
