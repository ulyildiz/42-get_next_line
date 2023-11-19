/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/19 18:45:20 by ulyildiz         ###   ########.fr       */
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

	temp = ft_strjoin(buffer, tmp);
	free(buffer);
	free(tmp);
	return (temp);
}

static char	check_newline(char *str)
{
	if (!str)
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

	if (!buffer)
		buffer = (char *)ft_calloc(1, 1);
	flag = 1;

	while (flag > 0 && check_newline(buffer) == '0')
	{	
		tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (tmp == NULL)
			return (NULL);
		flag = read(fd, tmp, BUFFER_SIZE);
		if (flag == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		buffer = dup_free(buffer, tmp);
		if (check_newline(buffer) == '1')
			break ;
	}

	return (buffer);
}

static char	*read_durability(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*static_durability(char *buffer)
{
	char	*newbuf;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (buffer[j] && buffer[j] != '\n')
		j++;
	if (!buffer[j])
	{
		free(buffer);
		return (NULL);
	}
	newbuf = (char *)ft_calloc(ft_strlen(buffer) - (j++) + 1, sizeof(char));
	if (newbuf == NULL)
	{
		free(buffer);
		return (NULL);
	}
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
//	printf("*%s*", get_next_line(fd));
//	printf("*%s*", get_next_line(fd));
	close(fd);
}*/
