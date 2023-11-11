/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line(2).c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:29:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/11 05:43:40 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> //?
#include "get_next_line.h"

static char	*read_file(int fd, char *buffer, char *tmp)
{
	int	i;

	i = read(fd, buffer, BUFFER_SIZE);
	if (i == -1)
	{
		free(buffer);
		return(NULL);
	}
	else if (i == 0)
		return (NULL);
	
}
static int	*check_newline(int fd, char *str)
{
	if (str == NULL)
		return (NULL);
	while (str != NULL)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char	*buffer;
	char	*line;
	char	*tmp;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	stack = read_file(fd, buffer, tmp);
	if (stack == NULL)
		return (NULL);
	
	
	return (line);
}