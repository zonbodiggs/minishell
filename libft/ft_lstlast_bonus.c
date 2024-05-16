/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:07 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 10:57:45 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstlast(t_stack *lst)
{
	t_stack	*tmp;
	t_stack	*res;

	tmp = lst;
	if (!lst)
		return (0);
	while (tmp)
	{
		res = tmp;
		tmp = tmp -> next;
	}
	return (res);
}
