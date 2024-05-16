/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 03:45:35 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/28 13:52:40 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_memcpy(res, s, ft_strlen(s));
	while (res[i] && i < ft_strlen(s))
	{
		res[i] = f(i, res[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
