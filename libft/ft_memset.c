/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:37:26 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/24 18:18:21 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*t_str;
	unsigned long	i;

	t_str = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		t_str[i] = c;
		i++;
	}
	return (t_str);
}
