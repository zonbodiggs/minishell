/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:20:56 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 10:57:53 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstmap(t_stack *lst, void *(*f)(void *), void (*del)(void *))
{
	t_stack	*new;
	t_stack	*res;
	void	*content;

	res = NULL;
	while (lst && f && del)
	{
		content = f(lst -> content);
		if (!content)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		new = ft_lstnew(content);
		if (!new)
		{
			(*del)(content);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, new);
		lst = lst -> next;
	}
	return (res);
}
