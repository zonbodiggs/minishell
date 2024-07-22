/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:56:32 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/22 16:45:52 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	sort_export(char **arr, int n)
{
	int 	i;
	int		j;
	char	*key;

	i = 1;
	while (i < n)
	{
		key = arr[i];
        j = i - 1;
        while (j >= 0 && ft_strncmp(arr[j], key, ft_strlen(arr[j])) > 0)
		{
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
		i++;
    }
}

static char **copy_env(char **dest, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static void	list_env_vars(char **env)
{
	char **env_sort;
	int i;
	int	count;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	count = count - 1;
	env_sort = malloc(count * sizeof(char *));
	if(!env_sort)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	env_sort = copy_env(env_sort, env, count);
	sort_export(env_sort, count);
	while (env_sort[i] != NULL)
	{
		printf("declare -x %s\n", env_sort[i]);
		i++;
	}
	/*i = 0;    j'arrive pas a free mdrr
	while(env_sort[i] != NULL)
	{
		free(env_sort[i]);
		i++;
	}
	free(env_sort);*/
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
