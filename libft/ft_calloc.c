/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:03:17 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/28 11:57:29 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t nsize)
{
	size_t	size;
	void	*ptr;

	if (num * nsize != 0 && (num * nsize) / num != nsize)
		return (NULL);
	size = num * nsize;
	ptr = malloc(size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size);
	return (ptr);
}
