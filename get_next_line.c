/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/11 19:26:31 by ulyildiz         ###   ########.fr       */
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

static char	*read_file(int fd, char *tmp, char *buffer)
{
	int	i;		

	i = read(fd, buffer, BUFFER_SIZE);
	while (check_newline(buffer) == '0')
	{
    	if (i == -1)
		{
        	free(buffer);
        	return (NULL);
        } 
		else if (i == 0)
			break ;
        if (tmp)
    		tmp = ft_strjoin(tmp, buffer);
		else
			tmp = ft_strdup(buffer);
		i = read(fd, buffer, BUFFER_SIZE);
	}
	if (i > 0)
		tmp = ft_strjoin(tmp, buffer);
	free(buffer);
	return (tmp);
}

static char	*read_durability(char *tmp, char *line)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
		i++;
	line = (char *)calloc(i + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

static char	*static_durability(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	i++;
	return (tmp + i);
}

char	*get_next_line(int fd)
{
	static char	*stack = NULL;
	char	*buffer = NULL;
	char	*line = NULL;
	char	*tmp = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);	
	buffer = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	tmp = read_file(fd, tmp, buffer);
	if (tmp == NULL)
		return (NULL);
	line = read_durability(tmp, line);
	if (line == NULL)
		return (NULL);
	if (stack)
	{
		line = ft_strjoin(stack, line);
		free(stack);
	}
	stack = ft_strdup(static_durability(tmp));
	if (stack == NULL)
		return (NULL);
	free(tmp);
	return (line);
}

int main()
{
	int fd = open("example.txt", O_RDONLY);
	printf("*%s*", get_next_line(fd));
	printf("*%s*", get_next_line(fd));
//	printf("*%s*", get_next_line(fd));
	//printf("*%s*", get_next_line(fd));

}