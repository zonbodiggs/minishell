/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:21:26 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/22 14:17:13 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd(t_minishell *minishell)
{
	char	cwd[PATH_MAX];
	char	*p;
	char	**pwd;

	p = ft_strjoin("export,PWD=", getcwd(cwd, sizeof(cwd)));
	pwd = ft_split(p, ',');
	export_variable(pwd, &minishell->env);
	free(p);
	free_array(pwd);
}

void	add_env(t_minishell *minishell)
{
	char	**shl;
	char	**path;
	char	*p;

	p = "export,PATH=/.local/bin:/usr/local" \
	"/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	shl = ft_split("export,SHLVL=1", ',');
	path = ft_split(p, ',');
	if (!minishell->env || !mygetenv("PWD", *minishell))
		add_pwd(minishell);
	if (!minishell->env || !mygetenv("SHLVL", *minishell))
		export_variable(shl, &minishell->env);
	if (!minishell->env || !mygetenv("PATH", *minishell))
		export_variable(path, &minishell->env);
	free_array(shl);
	free_array(path);
}

void	update_shlvl(t_minishell *minishell)
{
	char	*lvl;
	char	*tmp;
	int		i;

	i = 0;
	lvl = ft_itoa(ft_atoi(mygetenv("SHLVL", *minishell)) + 1);
	tmp = ft_strjoin("SHLVL=", lvl);
	if (tmp)
		set_env_var(&minishell->env, "SHLVL", tmp);
	while (ft_strncmp(minishell->env[i], "SHLVL", 5))
		i++;
	free(minishell->env[i]);
	minishell->env[i] = tmp;
	free(lvl);
}

char	*mygetenv(char *s, t_minishell mini)
{
	int		i;
	int		len;
	char	*res;

	len = 0;
	i = 0;
	if (!s || !s[0] || !mini.env)
		return (NULL);
	if (!ft_strncmp(s, "?", ft_strlen(s)))
		return (mini.exit_code);
	while (mini.env[i])
	{
		len = ft_strlen(mini.env[i]) - ft_strlen(ft_strchr(mini.env[i], '='));
		if (!ft_strncmp(s, mini.env[i], len) && (int)ft_strlen(s) == len)
		{
			res = ft_strchr(mini.env[i], '=') + 1;
			return (res);
		}
		i++;
	}
	return (NULL);
}
