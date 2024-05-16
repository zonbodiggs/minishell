/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 06:26:25 by endoliam          #+#    #+#             */
/*   Updated: 2024/04/06 09:56:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substrgnl(char const *s, unsigned int start, size_t len)
{
	size_t		t_size;
	char		*dest;

	t_size = ft_strlengnl(s);
	if (start >= t_size)
	{
		dest = malloc(1 * sizeof(char));
		dest[0] = '\0';
		return (dest);
	}
	if (start + len > t_size && len != start)
		len = t_size - start;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_memmove(dest, s + start, len);
	dest[len] = '\0';
	return (dest);
}

size_t	ft_strlengnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str)
		i++;
	return (i);
}

char	*ft_strchrgnl(char *str, int c)
{
	while (*str != c && str)
	{
		if (*str++ == 0)
			return (0);
	}
	return (str);
}

void	*ft_memmovegnl(void *dest, const void *src, size_t n)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;

	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (t_dest == t_src)
		return (dest);
	if (t_src > t_dest || t_dest >= t_src + n)
	{
		while (n--)
			*t_dest++ = *t_src++;
	}
	else
	{
		while (n--)
		{
			*(t_dest + n) = *(t_src + n);
		}
	}
	return (dest);
}

char	*ft_strjoingnl(char *next_line, const char *buffer)
{
	size_t		len;
	size_t		i;
	char		*res;

	i = -1;
	if (!next_line)
	{
		next_line = malloc(1 * sizeof(char *));
		if (!next_line)
			return (0);
		next_line[0] = '\0';
	}
	len = ft_strlengnl(next_line);
	res = malloc((len + ft_strlengnl(buffer) + 1) * sizeof(char *));
	if (!res)
		return (ft_free(&next_line));
	while (next_line[++i] != '\0')
		res[i] = next_line[i];
	i = -1;
	while (buffer[++i])
		res[i + len] = buffer[i];
	res[i + len] = '\0';
	free(next_line);
	return (res);
}
