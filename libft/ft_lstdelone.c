/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:41:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 10:57:29 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_stack *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (lst->content)
	{
		del(lst);
		free (lst);
	}
}
