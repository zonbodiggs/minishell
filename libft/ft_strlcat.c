/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:17:23 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:03:55 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t l)
{
	size_t		i;
	size_t		j;
	size_t		size;	

	i = 0;
	size = ft_strlen(dest);
	j = size;
	if (size < l - 1 && l > 0)
	{
		while (src[i] && size + i < l - 1)
		{
			dest[j] = src[i];
			i++;
			j++;
		}
		dest[j] = '\0';
	}
	if (l <= size)
		size = l;
	return (size + ft_strlen(src));
}
