/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:56:32 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/16 16:11:54 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sort_export(char **arr, int n)
{
	int		i;
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

static char	**copy_env(char **dest, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static void	list_env_vars(char **env)
{
	char	**env_sort;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	env_sort = malloc((count + 1) * sizeof(char *));
	if (!env_sort)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	env_sort = copy_env(env_sort, env, count);
	sort_export(env_sort, count);
	while (env_sort[i + 1] != NULL)
	{
		printf("declare -x %s\n", env_sort[i]);
		free(env_sort[i]);
		i++;
	}
	free(env_sort);
}

static int	validate_variable(char *var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (equal_sign == NULL)
	{
		printf("export: `%s`: not a valid identifier\n", var);
		return (0);
	}
	return (1);
}

int	export_variable(char **cmd, char ***env)
{
	char	*new_var;

	new_var = cmd[1];
	if (!*env)
		*env = ft_calloc(2, sizeof(char *));
	if (cmd[1] == NULL)
	{
		list_env_vars(*env);
		return (0);
	}
	if (!validate_variable(new_var))
		return (1);
	if (update_existing_var(new_var, env))
		return (0);
	if (!add_new_var(new_var, env))
		return (1);
	return (0);
}
