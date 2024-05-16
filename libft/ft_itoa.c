/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:27:57 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/28 13:45:55 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sizelen(long long n)
{
	size_t		size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static void	rev_tab(char *str, size_t size)
{
	size_t	i;
	char	temp;

	i = 0;
	while (i < size && str[i])
	{
		temp = str[i];
		str[i] = str[size - 1];
		str[size - 1] = temp;
		size--;
		i++;
	}
}

static int	ft_is_negative(int n, int neg)
{
	if (n < 0)
	{
		neg = 1;
	}
	else
		neg = 0;
	return (neg);
}

static char	*convertchar(long long num, char *res, int neg)
{
	size_t	i;

	i = 0;
	if (num == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	while (num != 0)
	{
		res[i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	if (neg == 1)
		res[i++] = '-';
	res[i] = '\0';
	rev_tab(res, ft_strlen(res));
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			neg;
	long long	num;

	neg = 0;
	num = n;
	neg = ft_is_negative(n, neg);
	if (neg == 1)
		num = -(long long)n;
	res = malloc((sizelen(num) + 1 + neg) * sizeof(char));
	if (!res)
		return (0);
	res = convertchar(num, res, neg);
	return (res);
}
