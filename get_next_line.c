/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:43:46 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/01 10:08:41 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <get_next_line.h>

static char	*ft_read_line(int fd)
{
	int	i;
	char	*rl;

	rl = (char *)malloc(BUFFER_SIZE + 1);
	i = read(fd, rl, BUFFER_SIZE + 1);
	if (i == -1)
	{
		free(rl);
		return (NULL);
	}
	else if (i == 0)
		return (NULL);
	return (rl);
}

void	ft_catch_newline(char *keep)
{
	
}

char	*get_next_line(int fd)
{
	static char	*line;
	
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
	
}
