/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:47:36 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:04:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char			*tmp;
	unsigned char	car;

	tmp = (char *)str;
	car = (unsigned char) c;
	while (*tmp)
	{
		if (*tmp == car)
			return (tmp);
		tmp++;
	}
	if (!car && !*tmp)
		return (tmp);
	return ((void *)0);
}
