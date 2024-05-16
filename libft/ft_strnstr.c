/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:05:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:02:10 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char		*temp;
	size_t		flen;

	if (!str && !to_find)
		return (0);
	temp = (char *)str;
	flen = ft_strlen(to_find);
	if (flen == 0)
		return ((char *)temp);
	while (*temp && len > 0)
	{
		if (ft_strncmp(temp, to_find, flen) == 0)
		{
			if (len < flen)
				return (0);
			return ((char *)temp);
		}
		len--;
		temp++;
	}
	return (0);
}
