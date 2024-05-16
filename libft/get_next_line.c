/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:49:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/04/06 10:04:14 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (0);
}

char	*ft_read(int fd, char *next_line)
{
	char	*buffer;
	int		bytesread;

	bytesread = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&next_line));
	buffer[0] = '\0';
	while (!ft_strchrgnl(buffer, '\n') && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread > 0)
		{
			buffer[bytesread] = '\0';
			next_line = ft_strjoingnl(next_line, buffer);
		}
	}
	free (buffer);
	if (bytesread == -1)
		return (ft_free(&next_line));
	return (next_line);
}

char	*ft_get_line(char *next_line, char *ptr)
{
	char	*line;
	int		len;

	len = (ptr - next_line) + 1;
	line = ft_substrgnl(next_line, 0, len);
	if (!line)
		return (0);
	return (line);
}

char	*go_next_line(char *next_line, char *ptr)
{
	int		len;
	char	*new_line;

	if (!ptr)
	{
		new_line = NULL;
		return (ft_free(&next_line));
	}
	else
		len = (ptr - next_line) + 1;
	if (!next_line[len])
		return (ft_free(&next_line));
	new_line = ft_substrgnl(next_line, len, ft_strlengnl(next_line) - len);
	ft_free(&next_line);
	if (!new_line)
		return (0);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*ptr;
	static char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if ((next_line != 0 && !ft_strchr(next_line, '\n')) || next_line == 0)
		next_line = ft_read(fd, next_line);
	if (!next_line)
		return (0);
	ptr = ft_strchrgnl(next_line, '\n');
	line = ft_get_line(next_line, ptr);
	if (line == 0)
		return (ft_free(&next_line));
	next_line = go_next_line(next_line, ptr);
	return (line);
}
