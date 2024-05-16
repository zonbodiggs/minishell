/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:26:20 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:00:21 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcmp(const char *set, char a)
{
	int		i;

	i = 0;
	while (*set)
	{
		if (*set - a == 0)
			i++;
		set++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*tmp;
	size_t	len;
	size_t	setlen;
	size_t	start;

	if (!s1 && !*set)
		return (0);
	tmp = (char *)s1;
	setlen = ft_strlen(set);
	len = ft_strlen(tmp);
	start = 0;
	if (setlen == 0 || (set == s1))
		setlen = ft_strlen(tmp);
	while (ft_charcmp(set, *tmp) != 0)
	{
		start++;
		tmp++;
	}
	while (ft_charcmp(set, tmp[len - start - 1]) != 0)
		len--;
	res = ft_substr(s1, start, len - start);
	if (!res)
		return (0);
	return (res);
}
