/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:31 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:03:09 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*t_s1;
	unsigned char	*t_s2;
	size_t			i;

	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	if (!*t_s1 && !*t_s2)
		return (0);
	while (i < (n - 1))
	{
		if (t_s1[i] != t_s2[i])
			return (t_s1[i] - t_s2[i]);
		if (!t_s1[i] && !t_s2[i])
			return (t_s1[i] - t_s2[i]);
		i++;
	}
	return (t_s1[i] - t_s2[i]);
}
