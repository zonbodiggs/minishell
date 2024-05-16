/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:03:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/16 11:10:22 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long					i;
	long					nbr;
	long					sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (ft_isdigit(nptr[i]))
	{
		if (nbr != (nbr * 10 + (nptr[i] - '0')) / 10)
			return ((int)(sign + 1) / 2 / -1);
		nbr = (nbr * 10) + (nptr[i++] - '0');
	}
	return (nbr * sign);
}
