/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:06:20 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/15 13:32:29 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;

	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (t_dest == t_src)
		return (dest);
	if (t_src > t_dest || t_dest >= t_src + n)
	{
		while (n--)
			*t_dest++ = *t_src++;
	}
	else
	{
		while (n--)
		{
			*(t_dest + n) = *(t_src + n);
		}
	}
	return (dest);
}
