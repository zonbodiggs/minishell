/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:06:28 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 15:30:12 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		t_size;
	char		*dest;

	if (!*s && !start && !len)
	{
		dest = ft_calloc(1, sizeof(char));
		return (dest);
	}
	t_size = ft_strlen(s);
	if (start >= t_size)
	{
		dest = ft_calloc(1, sizeof(char));
		if (!dest)
			return (NULL);
		return (dest);
	}
	if (start + len > t_size && len != start)
		len = t_size - start;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (0);
	ft_memmove(dest, s + start, len);
	return (dest);
}
