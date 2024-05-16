/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:05 by endoliam          #+#    #+#             */
/*   Updated: 2024/04/06 10:12:46 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t		len;
	char		*dest;

	len = ft_strlen(str);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, str, len);
	return (dest);
}
