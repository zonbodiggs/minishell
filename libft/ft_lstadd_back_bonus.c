/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:10:56 by endoliam          #+#    #+#             */
/*   Updated: 2024/04/06 10:04:57 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack		*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new -> prev = NULL;
	}
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
		new -> prev = last;
	}
}
