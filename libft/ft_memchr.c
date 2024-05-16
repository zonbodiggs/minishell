/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:04:06 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/24 18:37:55 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	tc;
	size_t			i;

	i = 0;
	tc = (unsigned char) c;
	tmp = (unsigned char *)str;
	while (i < n)
	{
		if (tmp[i] == tc)
			return (tmp + i);
		i++;
	}
	return ((void *)0);
}
