/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/25 10:42:04 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	free(buffer);
	return (temp);
}

static int	check_newline(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*read_file(int fd, char *buffer)
{
	char	*tmp;
	int		flag;		

	flag = 1;
	while (flag > 0 && 0 == check_newline(buffer))
	{
		tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (tmp == NULL || !tmp)
			return (NULL);
		flag = read(fd, tmp, BUFFER_SIZE);
		if (flag == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		buffer = dup_free(buffer, tmp);
		/*if (check_newline(tmp))
		{
			free(tmp);
			break ;
		}*/
		free(tmp);
	}
	return (buffer);
}

static char	*read_durability(char *buffer)
{
	char	*line;
	int		linelen;

	if (!buffer || buffer[0] == '\0' || buffer == NULL)
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
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		j++;
	if (buffer[j] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	newbuf = (char *)ft_calloc(ft_strlen(buffer) - (j++) + 1, sizeof(char));
	if (!newbuf || newbuf == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[j] != '\0') //?
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
	buffer = static_durability(buffer);
	return (line);
}
/*
int main()
{
	int fd = open("example.txt", O_RDONLY);
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