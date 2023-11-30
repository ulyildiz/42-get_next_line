/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:43:50 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/29 15:41:27 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_calloc(size_t count, size_t nbyte)
{
	void	*allc;
	size_t	i;

	allc = malloc(count * nbyte);
	if (!allc)
		return (NULL);
	i = 0;
	while (i < count * nbyte)
		((char *)allc)[i++] = '\0';
	return (allc);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	size_t		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s3 = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (*s1 != '\0')
		s3[i++] = *(s1++);
	while (*s2 != '\0')
		s3[i++] = *(s2++);
	return (s3);
}

int	check_newline(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
