/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:12:13 by hbenazza          #+#    #+#             */
/*   Updated: 2023/12/05 23:06:14 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len] != '\0')
		len++;
	return (len);
}

static char	*new_line(char *str)
{
	size_t	len;
	char	*line;

	len = 0;
	if (!str[len])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
	{
		line[len] = str[len];
		len++;
	}
	if (str[len] == '\n')
		line[len++] = '\n';
	line[len] = 0;
	return (line);
}

static char	*file(char *next, int fd, size_t buff)
{
	char	*buffer;
	ssize_t	i;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * (buff + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n') && i > 0)
	{
		i = read(fd, buffer, buff);
		if (i < 0)
		{
			free(buffer);
			free(next);
			return (NULL);
		}
		buffer[i] = '\0';
		next = ft_strjoin(next, buffer);
	}
	free(buffer);
	return (next);
}

static char	*shifting(char *str)
{
	size_t	i;
	size_t	j;
	char	*new;

	j = 0;
	i = 0;
	while (str[j] && str[j] != '\n')
		j++;
	if (str[j] == '\0')
	{
		free(str);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - j + 1));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	j++;
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*next[1024];
	char		*line;
	size_t		buff;

	buff = BUFFER_SIZE;
	if (fd < 0 || buff < 0)
		return (NULL);
	next[fd] = file(next[fd], fd, buff);
	if (!next[fd])
		return (NULL);
	line = new_line(next[fd]);
	next[fd] = shifting(next[fd]);
	return (line);
}
