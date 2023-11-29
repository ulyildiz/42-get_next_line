/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/29 12:24:27 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

static char	*dup_free(char *buffer, char *tmp)
{
	char	*temp;

	temp = 0;
	if (!buffer)
	{
		buffer = (char *)ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	temp = ft_strjoin(buffer, tmp);
	free(buffer);
	return (temp);
}

static char	*read_file(int fd, char *buffer)
{
	char	*tmp;
	int		flag;		

	flag = 1;
	tmp = 0;
	while (flag > 0 && 0 == check_newline(buffer))
	{
		tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!tmp)
		{
			if (buffer)
			{
				free(buffer);
				buffer = NULL;
			}
			return (NULL);
		}
		flag = read(fd, tmp, BUFFER_SIZE);
		if (flag == -1)
		{
			free(tmp);
			return (free(buffer), buffer = NULL, NULL);
		}
		if (flag > 0)
			buffer = dup_free(buffer, tmp);
		if (!buffer)
			return (free(tmp), NULL);
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
	if (!line || line == NULL)
		return (NULL);
	linelen = 0;
	while (buffer[linelen] != '\n' && buffer[linelen])
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
	newbuf = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n' && buffer)
		j++;
	if (!buffer || buffer[j] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	newbuf = (char *)ft_calloc(ft_strlen(buffer) - (j++) + 1, sizeof(char));
	if (!newbuf)
		return (free(buffer), buffer = NULL, NULL);
	i = 0;
	while (buffer[j] != '\0')
		newbuf[i++] = buffer[j++];
	free(buffer);
	return (newbuf);
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
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = static_durability(buffer);
	return (line);
}
/*
int main()
{
	int fd = open("/Users/ulyildiz/francinette/tests/get_next_line/fsoares/giant_line.txt", O_RDONLY);
	char *a;
	a = get_next_line(fd);
	printf("*%s*", a);
	free(a);
	char *b;
	b = get_next_line(fd);
	printf("*%s*", b);
	free(b);
	char *c = get_next_line(fd);
	printf("*%s*", c);
	free(c);
	char *d = get_next_line(fd);
	printf("*%s*", d);
	free(d);
	close(fd);
}
*/