/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:31 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/16 23:30:02 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*t_s1;
	unsigned char	*t_s2;
	size_t			i;

	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	if (!t_s1 && !t_s2)
		return (0);
	if (!t_s1 || !t_s2)
		return (1);
	i = 0;
	while (t_s1 && t_s2 && t_s1[i] && t_s2[i])
	{
		if (t_s1[i] != t_s2[i])
			return (t_s1[i] - t_s2[i]);
		if (!t_s1[i] && !t_s2[i])
			return (t_s1[i] - t_s2[i]);
		i++;
	}
	return (t_s1[i] - t_s2[i]);
}
