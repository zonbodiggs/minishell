/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:55:19 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/24 18:18:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char			*tmp;
	unsigned int			i;

	tmp = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}
