/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:05 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/20 19:20:04 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_qstrdup(const char *str)
{
	size_t		len;
	char		*dest;

	len = ft_strlen(str);
	dest = ft_calloc((len), sizeof(char));
	if (!dest)
		return (0);
	ft_memcpy(dest, str + 1, len - 2);
	return (dest);
}
