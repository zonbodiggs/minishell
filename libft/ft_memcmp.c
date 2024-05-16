/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:04:15 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/24 20:20:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				res;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (ft_strlen(s1) < n && ft_strlen(s2) < n)
	{
		while (n > 0)
		{
			if (*str1 != *str2)
				return (*str1 - *str2);
			str1++;
			str2++;
			n--;
		}
		return (0);
	}
	res = ft_strncmp((const char *)str1, (const char *) str2, n);
	return (res);
}
