/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:56:42 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:24:48 by endoliam         ###   ########lyon.fr   */
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
		else
		{
			if (i == 0)
			{
				size++;
				i = 1;
			}
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
	while (s[len] && s[len] != c)
		len++;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (str)
		ft_memcpy(str, s, len);
	return (str);
}

static void	freestr(char **res, size_t i)
{
	int	j;

	j = -1;
	while (j++ < (int)i)
		free(res[j]);
	free (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**res;

	res = ft_calloc((noccurrences(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[i++] = copy_str(s, c);
			if (res[i - 1] == 0)
			{
				freestr(res, i);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	return (res);
}
