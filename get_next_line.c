/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:43:46 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/01 10:38:30 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

static char	*ft_read_line(int fd)
{
	int			i;
	char	*rl;

	rl = (char *)malloc(BUFFER_SIZE + 1);
	if (rl == NULL)
		return (NULL);
	rl[BUFFER_SIZE] = '\0';
	i = read(fd, rl, BUFFER_SIZE);
	if (i == -1)
	{
		free(rl);
		return (NULL);
	}
	else if (i == 0)
		return (NULL);
	return (rl);
}

static int	ft_catch_newline(char *line, char *wwn)
{
	int	i;

	i = 0;
	wwn[BUFFER_SIZE] = '\0';
	while (line[i] != '\n' && line[i] != '\0')
	{
		wwn[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		wwn[i] = '\n';
	else if (line[i] == '\0')
		wwn[i] = '\0';
	free(line);
	return (i);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*wwn;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(BUFFER_SIZE + 1);
	if (line == NULL)
		return (NULL);
	line = ft_read_line(fd);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	wwn = (char *)malloc(BUFFER_SIZE + 1);
	if (wwn == NULL)
	{
		free(line);
		return (NULL);
	}		
	ft_catch_newline(line, wwn);
	return (wwn);
}
