/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/18 18:22:27 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

static char	check_newline(char *str)
{
	if (str == NULL)
		return ('\0');
	while (*str != '\0')
	{
		if (*str == '\n')
			return ('1');
		str++;
	}
	return ('0');
}

static char	*read_file(int fd, char *buffer)
{
	char	*tmp;
	int		flag;		

	flag = 1;
	tmp = (char *)calloc(BUFFER_SIZE + 1, 1);
	if (tmp == NULL)
		return (NULL);
	while (flag > 0)
	{
		flag = read(fd, tmp, BUFFER_SIZE);
		if (flag == -1)
		{
			free(tmp);
			return (NULL);
		}
		if (!buffer)
			buffer = ft_strdup(tmp);
		else
			buffer = ft_strjoin(buffer, tmp);
		if (check_newline(tmp) == '1')
			break ;
	}
	free(tmp);
	return (buffer);
}

static char	*read_durability(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = (char *)calloc(i + 2, 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*static_durability(char *buffer)
{
	char	*newbuf;
	int		i;

	i = 0;
	while (*buffer != '\n' && *buffer != '\0')
		buffer++;
	buffer++;
	while (buffer[i] != '\0')
		i++;
	newbuf = (char *)calloc(i + 1, 1);
	if (newbuf == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0')
	{
		newbuf[i] = buffer[i];
		i++;
	}
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
	if (*buffer == '\0')
		return (NULL);
	line = read_durability(buffer);
	/*if (line == NULL)
		return (NULL);
	*/
	/*if (!(line))
		return (NULL);*/
	if (*line == '\0')
		return (NULL);
	buffer = static_durability(buffer);
	return (line);
}

int main()
{
	int fd = open("example.txt", O_RDONLY);
	printf("*%s*", get_next_line(fd));
	printf("*%s*", get_next_line(fd));
	printf("*%s*", get_next_line(fd));
	printf("*%s*", get_next_line(fd));
	close(fd);
}
