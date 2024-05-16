/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:42:43 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:02:01 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*tmp;
	unsigned char	car;
	size_t			len;

	tmp = (char *)str;
	car = (unsigned char)c;
	len = ft_strlen(str);
	if (!tmp)
		return ((void *)0);
	while (len)
	{
		if (tmp[len] == car)
			return (tmp + len);
		len--;
	}
	if (tmp[len] == car)
		return (tmp);
	return ((void *)0);
}
