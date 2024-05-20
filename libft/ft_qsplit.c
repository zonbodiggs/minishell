/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:12:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/20 12:49:41 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	noccurrences(const char *s, char c)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (*s)
	{
		if (*s == c)
			i = 0;
		if (i == 0)
		{
			size++;
			i = 1;
		}
		s++;
	}
	return (size);
}

static char	*copy_str(const char *s, char c)
{
	size_t	len;
	char	*str;

	len = 0;
	if (*s == 39 || *s == '"')
	{
		s++;
		while (s[len] && s[len] != 39 && s[len] != '"')
			len++;
	}
	else
	{
		while (s[len] && s[len] != c)
			len++;
	}
	str = calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s, len);
	return (str);
}

static void	freestr(char **res, size_t i)
{
	int	j;

	j = -1;
	while (j++ < (int)i)
		free(res[j]);
	free(res);
}

static	char	**ft_pars_and_copy(const char *s, char **res, char c, int i)
{
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && s)
		{
			res[i++] = copy_str(s, c);
			if (res[i - 1] == 0)
			{
				freestr(res, i);
				return (NULL);
			}
			while (*s && ((*s != c) || (*(s - 1) == 39) || (*(s - 1) == '"')))
			{
				if (*s == 39 || *s == '"')
				{
					s++;
					while (*s && *s != 39 && *s != '"')
						s++;
				}
				s++;
			}
		}
	}
	return (res);
}

char	**ft_qsplit(char const *s, char c)
{
	size_t	i;
	char	**res;

	res = calloc((noccurrences(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	ft_pars_and_copy(s, res, c, i);
	return (res);
}
