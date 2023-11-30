/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/30 13:25:10 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

static char	*dup_free(char *buffer, char *tmp)
{
	char	*temp;

	if (!buffer)
	{
		buffer = (char *)ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	temp = ft_strjoin(buffer, tmp);
	return (free(buffer), temp);
}

static char	*read_file(int fd, char *buffer)
{
	char	*tmp;
	int		flag;		

	flag = 1;
	while (flag > 0)
	{
		tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!tmp)
		{
			if (buffer)
				return (free(buffer), buffer = NULL, NULL);
			return (NULL);
		}
		flag = read(fd, tmp, BUFFER_SIZE);
		if (flag == -1)
			return (free(tmp), free(buffer), buffer = NULL, NULL);
		else if (flag > 0)
			buffer = dup_free(buffer, tmp);
		if (!buffer)
			return (free(tmp), NULL);
		if (check_newline(tmp) && flag > 0)
			return (free(tmp), buffer);
		free(tmp);
	}
	return (buffer);
}

static char	*read_durability(char *buffer)
{
	char	*line;
	int		linelen;

	if (!buffer)
		return (NULL);
	linelen = check_newline(buffer);
	if (linelen == 0)
		linelen = ft_strlen(buffer);
	if (linelen == 0)
		return (NULL);
	line = (char *)ft_calloc(linelen + 1, sizeof(char));
	if (!line)
		return (NULL);
	linelen = 0;
	while (buffer[linelen] != '\n' && buffer[linelen] != '\0')
	{
		line[linelen] = buffer[linelen];
		linelen++;
	}
	if (buffer[linelen] == '\n')
		line[linelen] = '\n';
	return (line);
}

static char	*static_durability(char *buffer)
{
	char	*newbuf;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[j] != '\0' && buffer[j] != '\n' && buffer)
		j++;
	if (buffer[j] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	newbuf = (char *)ft_calloc(ft_strlen(buffer) - (j++) + 1, sizeof(char));
	if (!newbuf)
		return (free(buffer), buffer = NULL, NULL);
	i = 0;
	while (buffer[j] != '\0')
		newbuf[i++] = buffer[j++];
	return (free(buffer), newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = read_durability(buffer);
	if (!line)
	{
		if (buffer)
			return (free(buffer), buffer = NULL, NULL);
		return (NULL);
	}
	buffer = static_durability(buffer);
	return (line);
}
