#include "../minishell.h"

static void remove_var(char ***env, int index)
{
	int i = 0;
	int j = 0;
	char **new_env;

	while ((*env)[i])
		i++;
	new_env = malloc(i * sizeof(char *));
	if (!new_env)
	{
		perror("malloc");
		return;
	}
	i = 0;
	while ((*env)[i])
	{
		if (i != index)
		{
		    new_env[j] = (*env)[i];
		    j++;
		}
		else
		{
		    free((*env)[i]);
		}
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
}

static int find_var_index(char **env, const char *var)
{
	int i = 0;
	int len = ft_strlen(var);

	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return i;
		i++;
	}
	return -1;
}

int unset_variable(char **cmd, char ***env)
{
	int i = 1;
	int index;
	printf("\n\n\n\n\n\n%s\n\n\n\n\n\n\n", "testtesttesttesttesttesttesttesttesttesttesttest");
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
