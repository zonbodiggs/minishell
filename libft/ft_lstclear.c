/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:08:54 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:05:46 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_stack **lst, void (*del)(void*))
{
	t_stack	*liste;

	if (!lst)
		return ;
	liste = *lst;
	while (*lst)
	{
		liste = liste-> next;
		ft_lstdelone(*lst, del);
		*lst = liste;
	}
	*lst = 0;
}
