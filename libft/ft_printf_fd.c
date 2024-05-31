/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:58:47 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/31 14:04:33 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_conversions(int fd, va_list arg, const char str, int *addrcheck)
{
	long long	p;

	if (str == 'c')
		ft_putcharft(fd, va_arg(arg, int), addrcheck);
	else if (str == 's')
		ft_putstrft(fd, va_arg(arg, char *), addrcheck);
	else if (str == 'p')
	{
		p = va_arg(arg, long long);
		if (!p)
			return (ft_putstrft(fd, "(nil)", addrcheck));
		ft_putstrft(fd, "0x", addrcheck);
		ft_putnbr_hexaft(fd, p, addrcheck, 1);
	}
	else if (str == 'd' || str == 'i')
		ft_putnbrft(fd, va_arg(arg, int), addrcheck);
	else if (str == 'u')
		ft_putnbrft(fd, va_arg(arg, unsigned int), addrcheck);
	else if (str == 'x')
		ft_putnbr_hexaft(fd, va_arg(arg, unsigned int), addrcheck, 1);
	else if (str == 'X')
		ft_putnbr_hexaft(fd, va_arg(arg, unsigned int), addrcheck, 0);
	else if (str == '%')
		ft_putcharft(fd, '%', addrcheck);
}

int	ft_check_error(va_list arg)
{
	va_end(arg);
	return (-1);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int			i;
	int			check_write;
	va_list		arg;

	i = 0;
	check_write = 0;
	if (!str)
		return (-1);
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (ft_check_error(arg));
			ft_conversions(fd, arg, str[i + 1], &check_write);
			i++;
		}
		else
			ft_putcharft(fd, str[i], &check_write);
		i++;
	}
	va_end(arg);
	return (check_write);
}
