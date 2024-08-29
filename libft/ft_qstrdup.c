/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:05 by endoliam          #+#    #+#             */
/*   Updated: 2024/08/28 14:05:18 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_qstrdup(const char *str)
{
	size_t		len;
	char		*dest;

	len = ft_strlen(str);
	if (!ft_strcmp(str, """"))
	{
		dest = ft_calloc(1, sizeof(char));
		dest = NULL;
		return (dest);
	}
	dest = ft_calloc((len), sizeof(char));
	if (!dest)
		return (0);
	ft_memcpy(dest, str + 1, len - 2);
	return (dest);
}
