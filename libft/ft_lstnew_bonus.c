/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:30:07 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 13:18:30 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstnew(void *content)
{
	t_stack	*element;

	element = malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element -> content = content;
	element -> next = NULL;
	return (element);
}
