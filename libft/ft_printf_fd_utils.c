/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:59:25 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/31 14:53:56 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcharft(int fd, char c, int *addrcheck)
{
	if ((write (fd, &c, 1)) != -1)
		(*addrcheck)++;
}

size_t	ft_strlenft(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstrft(int fd, const char *str, int *addrcheck)
{
	size_t	size;

	if (!str)
	{
		ft_putstrft(fd, "(null)", addrcheck);
		return ;
	}
	size = ft_strlenft(str);
	if (write (fd, str, size) != -1)
		(*addrcheck) += size;
}

void	ft_putnbrft(int fd, long long n, int *addrcheck)
{
	if (n < 0)
	{
		ft_putcharft(fd, '-', addrcheck);
		n = n * -1;
		ft_putnbrft(fd, n, addrcheck);
	}
	else if (n > 9)
	{
		ft_putnbrft(fd, (n / 10), addrcheck);
		ft_putnbrft(fd, (n % 10), addrcheck);
	}
	else
		ft_putcharft(fd, n + '0', addrcheck);
}

void	ft_putnbr_hexaft(int fd, unsigned long n, int *addrcheck, int c)
{
	char	*base;

	if (c == 1)
		base = "0123456789abcdef";
	else if (c == 0)
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_putnbr_hexaft(fd, (n / 16), addrcheck, c);
		ft_putcharft(fd, base[n % 16], addrcheck);
	}
	else
		ft_putcharft(fd, base[n % 16], addrcheck);
}
